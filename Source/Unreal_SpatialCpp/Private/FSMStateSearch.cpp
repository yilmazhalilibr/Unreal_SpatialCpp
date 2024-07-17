// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMStateSearch.h"
#include "MasterAiShooter.h"
#include "MasterAiController.h"
#include "TimerManager.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include <Kismet/KismetMathLibrary.h>


void UFSMStateSearch::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Search State"));

	MasterAiController = Cast<AMasterAiController>(GetOuter());
	AIShooter = Cast<AMasterAiShooter>(MasterAiController->GetPawn());

	if (!MasterAiController)
	{
		UE_LOG(LogTemp, Warning, TEXT("MasterAiController is not valid"));
	}
	else
	{
		SetSearchLocation(MasterAiController->GetPlayerLastLocation());
		MasterAiController->ReceiveMoveCompleted.AddDynamic(this, &UFSMStateSearch::OnMoveCompleted);

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(AIShooter->GetActorLocation(), GetSearchLocation());
		AIShooter->SetActorRotation(LookAtRotation);


	/*	GetWorld()->GetTimerManager().SetTimer(LookAtTimerHandle, [this]()
			{

				if (AIShooter)
				{
					FRotator CurrentRotation = AIShooter->GetActorRotation();
					FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(AIShooter->GetActorLocation(), GetSearchLocation());
					FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 2.0f);

					AIShooter->SetActorRotation(NewRotation);

					if (NewRotation.Equals(TargetRotation, 1.0f))
					{
						GetWorld()->GetTimerManager().ClearTimer(LookAtTimerHandle);
					}
				}
			}, 1, true, 0.1);*/


		UE_LOG(LogTemp, Warning, TEXT("Search Location is %s"), *GetSearchLocation().ToString());
	}
	if (!AIShooter)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIShooter is not valid"));
	}


}

void UFSMStateSearch::Update(float DeltaTime)
{
	SetSearchLocation(MasterAiController->GetPlayerLastLocation());

	if (MasterAiController && GetSearchLocation() != FVector::Zero())
	{
		if (MasterAiController->MoveToLocation(GetSearchLocation(), 1.0f))
		{
			UE_LOG(LogTemp, Warning, TEXT("Searching for player"));

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Search Location is not valid"));
		}
	}

}

void UFSMStateSearch::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Search State"));

	if (MasterAiController)
	{
		//Stop Movement

		MasterAiController->StopMovement();
		MasterAiController->ReceiveMoveCompleted.RemoveDynamic(this, &UFSMStateSearch::OnMoveCompleted);

		//Stop LookAtTimerHandle
		GetWorld()->GetTimerManager().ClearTimer(LookAtTimerHandle);

	}


}

void UFSMStateSearch::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Search Location Reached"));

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				// ETC....


			}, 1.0f, false);


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Search Location Not Reached"));
	}
}


