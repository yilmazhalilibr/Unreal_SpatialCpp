// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterAiController.h"
#include "MasterAiShooter.h"
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

	// Sight Config oluþtur ve ayarla
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{

		SightConfig->SightRadius = SightRadius;
		SightConfig->LoseSightRadius = SightLoseRadius;
		SightConfig->PeripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;




		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		AIPerceptionComponent->ConfigureSense(*SightConfig);
		AIPerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
		UE_LOG(LogTemp, Warning, TEXT("Perception Success : %f "), SightRadius);


	}

	// Algýlama olayýný baðla
	/*AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AMasterAiController::OnPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &AMasterAiController::OnTargetPerceptionForgotten);*/

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMasterAiController::OnTargetPerceptionUpdated);

}

void AMasterAiController::BeginPlay()
{
	Super::BeginPlay();

	AiShooter = Cast<AMasterAiShooter>(GetPawn());
	if (AiShooter)
	{
		AiShooter = Cast<AMasterAiShooter>(GetOuter());

		if (AiShooter)
		{
			AiShooter->SetPerceptionProperties(SightRadius, SightLoseRadius, PeripheralVisionAngleDegrees);
		}

	}



	CurrentState = NewObject<UFSMBase>(this);
	IdleState = NewObject<UFSMStateIdle>(this);
	WalkState = NewObject<UFSMStateWalk>(this);
	RunState = NewObject<UFSMStateRun>(this);
	AttackState = NewObject<UFSMStateAttack>(this);
	ChaseState = NewObject<UFSMStateChase>(this);

	//Set default controller

	CurrentState = IdleState;
	CurrentState->Enter();


}

void AMasterAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterAiController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("Target Seen: %s"), *Actor->GetName());
			bIsPlayerDetected = true;
			//UE_LOG(LogTemp, Warning, TEXT("Target Distance: %s"), bIsPlayerDetected ? TEXT("true") : TEXT("false"));

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Target Lost: %s"), *Actor->GetName());
			bIsPlayerDetected = false;
			//UE_LOG(LogTemp, Warning, TEXT("Target Distance: %s"), bIsPlayerDetected ? TEXT("true") : TEXT("false"));

		}

	}
}



void AMasterAiController::AILogicTick(float DeltaTime)
{
	//Bool conditions and checks valid to AI Logic
	if (!AiShooter)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Shooter is not valid"));
		return;
	}
	else
	{
		//Check distance to player
		if (AiShooter->GetDistanceTo(GetWorld()->GetFirstPlayerController()->GetPawn()) < AiShooter->GetAttackDistance())
		{
			bIsPlayerInAttackRange = true;
			//UE_LOG(LogTemp, Warning, TEXT("Player is in attack range"));
		}
		else
		{
			bIsPlayerInAttackRange = false;


		}
		if (AiShooter->GetCurrentHP() < AiShooter->GetMaxHP() / 2.0f)
		{
			bPawnLowHasLowHp = true;
			//UE_LOG(LogTemp, Warning, TEXT("Pawn has low hp"));
		}
		else
		{
			bPawnLowHasLowHp = false;

		}

	}

	//Check conditions to AI Logic
	if (HandleChangeLogic() != CurrentState)
	{
		ChangeStateAI(HandleChangeLogic());
	}


	//Classic FSM
	if (GetCurrentState())
	{
		GetCurrentState()->Update(DeltaTime);
		//UE_LOG(LogTemp, Warning, TEXT("Current State is valid"));
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