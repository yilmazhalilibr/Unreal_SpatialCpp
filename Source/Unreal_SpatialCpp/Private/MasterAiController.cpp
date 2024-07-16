#include "MasterAiController.h"
#include "MasterAiShooter.h"
#include "FSMBase.h"
#include "FSMStateIdle.h"
#include "FSMStateWalk.h"
#include "FSMStateRun.h"
#include "FSMStateAttack.h"
#include "FSMStateChase.h"
#include "FSMStateCover.h"

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

	CurrentState = IdleState;
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
	if (bIsPlayerDetected)
	{
		if (bIsPlayerInAttackRange)
		{
			if (bPawnLowHasLowHp)
			{
				UE_LOG(LogTemp, Warning, TEXT("Cover"));
				return CoverState;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Attack"));
				return AttackState;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Chase"));
			return ChaseState;
		}
	}
	else
	{
		return IdleState;
	}
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
