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
#include <MasterAiSpawner.h>


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
		bSuspicion = true;
		bMissingPlayerTimer = 0.0f;

	}
	else
	{
		bMissingPlayerTimer += DeltaTime;
		bSuspicion = false;
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
		if (Stimulus.WasSuccessfullySensed() && Actor->Tags.Contains("Player"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Target Seen: %s"), *Actor->GetName());
			PlayerLastLocation = Stimulus.StimulusLocation;
			bIsPlayerDetected = true;
			bSearchDoOnce = false;

		}
		else if (Stimulus.WasSuccessfullySensed() && Actor->Tags.Contains("Player"))
		{
			PlayerLastLocation = Stimulus.StimulusLocation;
			bIsPlayerDetected = false;

			UE_LOG(LogTemp, Warning, TEXT("Target Lost: %s"), *Actor->GetName());

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
		auto* _spawner = Cast<AMasterAiSpawner>(AiShooter->GetOwner());
		if (_spawner)
		{
			_spawner->WarningPlayerDetected(true);
		}
	}
	/*else
	{
		OnWarMode = false;
	}*/
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
//
//UFSMBase* AMasterAiController::HandleChangeLogic()
//{
//	if (AiShooter->GetAIDead())
//	{
//		return DeadState;
//	}
//
//	if (!bIsPlayerDetected && !OnWarMode && !bAiInSearch)
//	{
//		return PatrolState;
//	}
//	else if (!bIsPlayerDetected && OnWarMode && bMissingPlayer)
//	{
//		return SearchState;
//	}
//	else if (!OnWarMode && bSuspicion || !OnWarMode && bSuspicion)
//	{
//		return SearchState;
//	}
//	else if (!bIsPlayerDetected && !bIsPlayerInAttackRange && OnWarMode)
//	{
//		return ChaseState;
//	}
//	else if (bIsPlayerDetected && bIsPlayerInAttackRange && OnWarMode)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Attack State %s"), bIsPlayerDetected ? TEXT("TRUE") : TEXT("FALSE"));
//
//		return AttackState;
//	}
//	else if (!bIsPlayerDetected && OnWarMode && bMissingPlayer && !bAiInSearch)
//	{
//		SetOnWarMode(false);
//		bMissingPlayer = false;
//		return ResetAIState;
//	}
//	else if (!bIsPlayerDetected && !OnWarMode && bMissingPlayer)
//	{
//		return IdleState;
//	}
//	else if (bPawnLowHasLowHp)
//	{
//		return CoverState;
//		//Belki burada can doldurma iþlemi yaptýrýrýz. Ona göre bir bool koyup Cover tamamlanýrsa yani can dolarsa tekrar bu stateden çýksýn yapabiliriz.
//	}
//
//
//
//	if (CurrentState == SearchState && !bSearchDoOnce)
//	{
//		ChangeStateAI(SearchState);
//		bSearchDoOnce = true;
//	}
//
//	return CurrentState;
//
//}
UFSMBase* AMasterAiController::HandleChangeLogic()
{
	if (AiShooter->GetAIDead())
	{
		return DeadState;
	}

	if (bIsPlayerDetected)
	{
		if (!OnWarMode && bSuspicion)
		{
			return SearchState;
		}

		if (OnWarMode)
		{
			if (bIsPlayerInAttackRange)
			{
				if (CurrentState != AttackState) // Eðer mevcut state AttackState deðilse
				{
					return AttackState;
				}
			}
			else
			{
				return ChaseState;
			}
		}
	}
	else
	{
		if (!OnWarMode)
		{
			if (!bSuspicion)
			{
				return PatrolState;
			}
			else
			{
				bAiInSearch = true; // Search durumuna girdiðini belirtiyoruz.
				return SearchState;
			}

			//if (bSuspicion && !bAiInSearch)
			//{
			//	bAiInSearch = true; // Search durumuna girdiðini belirtiyoruz.
			//	return SearchState;
			//}
		}
		else
		{
			if (bMissingPlayer)
			{
				SetOnWarMode(false);
				bMissingPlayer = false;
				bAiInSearch = false; // Reset AI durumuna geçtiðimizde Search durumu sýfýrlanýr.
				return ResetAIState;
			}
			else
			{
				//return SearchState;
				return ChaseState;
			}
		}
	}

	if (bPawnLowHasLowHp && OnWarMode)
	{
		return CoverState;
	}

	if (CurrentState == SearchState && !bSearchDoOnce)
	{
		bSearchDoOnce = true;
		return SearchState;
	}

	return CurrentState;
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
