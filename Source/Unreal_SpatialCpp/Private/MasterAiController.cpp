// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterAiController.h"
#include "MasterAiShooter.h"
#include "Perception/AIPerceptionComponent.h"





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
	}

	// Algýlama olayýný baðla
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AMasterAiController::OnPerceptionUpdated);

}

void AMasterAiController::BeginPlay()
{
	Super::BeginPlay();

	

}



void AMasterAiController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{

}

