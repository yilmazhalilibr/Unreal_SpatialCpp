// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMStateResetAI.h"
#include "MasterAiShooter.h"
#include "MasterAiController.h"



void UFSMStateResetAI::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering ResetAI State"));

	SetMasterAiController(Cast<AMasterAiController>(GetOuter()));
	SetAIShooter(Cast<AMasterAiShooter>(GetMasterAiController()->GetPawn()));

	if (!MasterAiController)
	{
		UE_LOG(LogTemp, Warning, TEXT("MasterAiController is not valid"));
	}
	else
	{
		FVector _spawnLoc = GetAIShooter()->GetSpawnLocation();

		GetMasterAiController()->MoveToLocation(_spawnLoc, 1.0f);

		AALSBaseCharacter* OwnerAI = Cast<AALSBaseCharacter>(GetAIShooter());

		OwnerAI->SetOverlayState(EALSOverlayState::Rifle);


	}
	if (!AIShooter)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIShooter is not valid"));
	}
}

void UFSMStateResetAI::Update(float DeltaTime)
{
}

void UFSMStateResetAI::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting ResetAI State"));

}
