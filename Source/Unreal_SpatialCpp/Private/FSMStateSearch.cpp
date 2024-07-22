// Fill out your copyright notice in the Description page of Project Settings.

#include "FSMStateSearch.h"
#include "MasterAiShooter.h"
#include "MasterAiController.h"
#include "TimerManager.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "GameFramework/CharacterMovementComponent.h"




void UFSMStateSearch::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Search State"));
	bRotationDone = false;

	MasterAiController = Cast<AMasterAiController>(GetOuter());
	AIShooter = Cast<AMasterAiShooter>(MasterAiController->GetPawn());

	//Character Move speed 400 adjust
	
	if (!MasterAiController)
	{
		UE_LOG(LogTemp, Warning, TEXT("MasterAiController is not valid"));
	}
	else
	{
		SetSearchLocation(MasterAiController->GetPlayerLastLocation());
		MasterAiController->ReceiveMoveCompleted.AddDynamic(this, &UFSMStateSearch::OnMoveCompleted);
		MasterAiController->StopMovement();
		MasterAiController->SetAiInSearch(true);
		
		AIShooter->GetCharacterMovement()->MaxWalkSpeed = 400.0f;

		UE_LOG(LogTemp, Warning, TEXT("Search Location is %s"), *GetSearchLocation().ToString());
	}
	if (!AIShooter)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIShooter is not valid"));
	}
}

void UFSMStateSearch::Update(float DeltaTime)
{
	/*FVector PlayerLocation = MasterAiController->GetPlayerLastLocation();
	MasterAiController->MoveToLocation(PlayerLocation, 5.0f);*/

	//if (!bRotationDone)
	//{
	//	SmoothLookAt(MasterAiController->GetPlayerLastLocation(), DeltaTime, 2.0f); // 2 saniyede dönmek için 0.5 hýz
	//}


	if (LookTimer >= AIShooter->GetSuspicionTime())
	{
		LookTimer = 0;
		MasterAiController->SetOnWarMode(true);
		MasterAiController->bAiInSearch = false;
		return;
	}

	LookTimer += DeltaTime;


}

void UFSMStateSearch::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Search State"));

	if (MasterAiController)
	{
		//Location equals zero
		SetSearchLocation(FVector::ZeroVector);
		MasterAiController->StopMovement();
		MasterAiController->SetAiInSearch(false);
		MasterAiController->ReceiveMoveCompleted.RemoveDynamic(this, &UFSMStateSearch::OnMoveCompleted);
		AIShooter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	}
}

void UFSMStateSearch::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Search Location Reached"));

		bRotationDone = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Search Location Not Reached"));
	}
}

void UFSMStateSearch::SmoothLookAt(FVector TargetLocation, float DeltaTime, float RotationSpeed)
{
	if (AIShooter)
	{
		FRotator CurrentRotation = AIShooter->GetActorRotation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(AIShooter->GetActorLocation(), TargetLocation);
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);

		AIShooter->SetActorRotation(NewRotation);

		if (FMath::Abs(CurrentRotation.Yaw - TargetRotation.Yaw) < 1.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Rotation Completed"));
			bRotationDone = true;
			MoveToSearchLocation();
		}
	}
}

void UFSMStateSearch::MoveToSearchLocation()
{

	if (MasterAiController && GetSearchLocation() != FVector::Zero())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Searching for Move To"));

		if (MasterAiController->MoveToLocation(GetSearchLocation(), 5.0f))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Searching 1111111111"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Search Location is not valid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Move To - %s"), bRotationDone ? TEXT("True") : TEXT("False"));
		UE_LOG(LogTemp, Warning, TEXT("Search Location is not valid"), MasterAiController->IsValidLowLevel() ? TEXT("MasterAIController Valid") : TEXT("MasterAIController Not Valid"));

	}


}
