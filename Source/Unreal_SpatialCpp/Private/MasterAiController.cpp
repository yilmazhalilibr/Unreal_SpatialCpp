#include "MasterAiController.h"
#include "MasterAiShooter.h"
#include "FSMBase.h"
#include "FSMStateIdle.h"
#include "FSMStateWalk.h"
#include "FSMStateRun.h"
#include "FSMStateAttack.h"
#include "FSMStateChase.h"
#include "FSMStateCover.h"
#include "FSMStatePatrol.h"
#include "FSMStateDead.h"
#include "FSMStateSearch.h"
#include "FSMStateResetAI.h"


AMasterAiController::AMasterAiController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		AIPerceptionComponent->ConfigureSense(*SightConfig);
		AIPerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
	}

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMasterAiController::OnTargetPerceptionUpdated);
}

void AMasterAiController::BeginPlay()
{
	Super::BeginPlay();
}

void AMasterAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPlayerDetected)
	{
		bSuspicionTimer += DeltaTime;
		bMissingPlayerTimer = 0.0f;

	}
	else
	{
		bMissingPlayerTimer += DeltaTime;
		bSuspicionTimer = 0.0f;

	}

	if (OnPossesDone && AiShooter && CurrentState)
	{
		AILogicTick(DeltaTime);
	}
}

void AMasterAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AiShooter = Cast<AMasterAiShooter>(InPawn);
	if (!AiShooter)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Shooter is not valid Pawn"));
		return;
	}

	if (SightConfig)
	{
		SightConfig->SightRadius = AiShooter->GetSightRadius();
		SightConfig->LoseSightRadius = AiShooter->GetSightLoseRadius();
		SightConfig->PeripheralVisionAngleDegrees = AiShooter->GetPeripheralVisionAngleDegrees();

		UE_LOG(LogTemp, Warning, TEXT("Perception Success : %f "), AiShooter->GetSightRadius());
	}

	CurrentState = NewObject<UFSMBase>(this);
	IdleState = NewObject<UFSMStateIdle>(this);
	WalkState = NewObject<UFSMStateWalk>(this);
	RunState = NewObject<UFSMStateRun>(this);
	AttackState = NewObject<UFSMStateAttack>(this);
	ChaseState = NewObject<UFSMStateChase>(this);
	CoverState = NewObject<UFSMStateCover>(this);
	PatrolState = NewObject<UFSMStatePatrol>(this);
	DeadState = NewObject<UFSMStateDead>(this);
	SearchState = NewObject<UFSMStateSearch>(this);
	ResetAIState = NewObject<UFSMStateResetAI>(this);


	CurrentState = IdleState;
	//CurrentState = IdleState;
	CurrentState->Enter();

	OnPossesDone = true;
}

void AMasterAiController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("Target Seen: %s"), *Actor->GetName());
			bIsPlayerDetected = true;
			PlayerLastLocation = Stimulus.StimulusLocation;

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Target Lost: %s"), *Actor->GetName());
			bIsPlayerDetected = false;
		}
	}
}

void AMasterAiController::AILogicTick(float DeltaTime)
{
	if (!AiShooter)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Shooter is not valid"));
		return;
	}

	if (AiShooter->GetDistanceTo(GetWorld()->GetFirstPlayerController()->GetPawn()) < AiShooter->GetAttackDistance())
	{
		bIsPlayerInAttackRange = true;
	}
	else
	{
		bIsPlayerInAttackRange = false;
	}

	if (AiShooter->GetCurrentHP() < AiShooter->GetMaxHP() / 2.0f)
	{
		bPawnLowHasLowHp = true;
	}
	else
	{
		bPawnLowHasLowHp = false;
	}
	if (bSuspicionTimer >= AiShooter->GetSuspicionTime())
	{
		OnWarMode = true;
	}
	else
	{
		OnWarMode = false;
	}
	if (bMissingPlayerTimer >= AiShooter->GetPlayerLostTime())
	{
		bMissingPlayer = true;
	}
	else
	{
		bMissingPlayer = false;
	}


	if (HandleChangeLogic() != CurrentState)
	{
		ChangeStateAI(HandleChangeLogic());
	}

	if (GetCurrentState())
	{
		GetCurrentState()->Update(DeltaTime);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Current State is not valid"));
	}
}

UFSMBase* AMasterAiController::HandleChangeLogic()
{
	if (AiShooter->GetAIDead())
	{
		return DeadState;
	}
	if (!bIsPlayerDetected && !OnWarMode)
	{
		return PatrolState;
	}
	else if (!bIsPlayerDetected && OnWarMode && bMissingPlayer)
	{
		return ResetAIState;
	}
	else if (!bIsPlayerDetected && OnWarMode)
	{
		return SearchState;
	}
	else if (!bIsPlayerDetected && !OnWarMode && bMissingPlayer)
	{
		return IdleState;
	}
	else if (bIsPlayerDetected && !bIsPlayerInAttackRange && OnWarMode)
	{
		return ChaseState;
	}
	else if (bIsPlayerDetected && bIsPlayerInAttackRange && OnWarMode)
	{
		return AttackState;
	}
	else if (bPawnLowHasLowHp)
	{
		return CoverState;
		//Belki burada can doldurma i�lemi yapt�r�r�z. Ona g�re bir bool koyup Cover tamamlan�rsa yani can dolarsa tekrar bu stateden ��ks�n yapabiliriz.
	}



	return IdleState;


}

void AMasterAiController::ChangeStateAI(UFSMBase* NewState)
{
	if (CurrentState)
	{
		CurrentState->Exit();
	}

	CurrentState = NewState;

	if (CurrentState)
	{
		CurrentState->Enter();
	}
}
