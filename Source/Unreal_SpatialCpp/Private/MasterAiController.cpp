// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterAiController.h"
#include "MasterAiShooter.h"
#include "Perception/AIPerceptionComponent.h"
#include "MasterAiShooter.h"
#include "FSMBase.h"




AMasterAiController::AMasterAiController()
{

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);

	// Sight Config oluþtur ve ayarla
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{

		AiShooter = Cast<AMasterAiShooter>(GetOuter());

		if (AiShooter)
		{
			AiShooter->SetPerceptionProperties(SightRadius, SightLoseRadius, PeripheralVisionAngleDegrees);
			SightConfig->SightRadius = SightRadius;
			SightConfig->LoseSightRadius = SightLoseRadius;
			SightConfig->PeripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;
			UE_LOG(LogTemp, Warning, TEXT("Perception Success : %f "), SightRadius);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Perception Failed"));
		}



		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		AIPerceptionComponent->ConfigureSense(*SightConfig);
		AIPerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());

	}

	// Algýlama olayýný baðla
	/*AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AMasterAiController::OnPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &AMasterAiController::OnTargetPerceptionForgotten);*/

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMasterAiController::OnTargetPerceptionUpdated);

}

void AMasterAiController::BeginPlay()
{
	Super::BeginPlay();

	if (!AiShooter)
	{
		AiShooter = Cast<AMasterAiShooter>(GetOuter());
	}

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
	if (HandleChangeLogic() != AiShooter->GetCurrentStateEnum())
	{
		AiShooter->ChangeStateAI(HandleChangeLogic());
	}


	//Classic FSM
	if (AiShooter->GetCurrentState())
	{
		AiShooter->GetCurrentState()->Update(DeltaTime);
		//UE_LOG(LogTemp, Warning, TEXT("Current State is valid"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Current State is not valid"));
	}


}

EState AMasterAiController::HandleChangeLogic()
{
	if (bIsPlayerDetected)
	{
		if (bIsPlayerInAttackRange)
		{
			if (bPawnLowHasLowHp)
			{
				UE_LOG(LogTemp, Warning, TEXT("Cover"));
				return EState::Cover;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Attack"));
				return EState::Attack;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Chase"));
			return EState::Chase;
		}
	}
	else
	{
		return EState::Idle;
	}

}