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



}

void AMasterAiController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("Target Seen: %s"), *Actor->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Target Lost: %s"), *Actor->GetName());
		}

	}
}


