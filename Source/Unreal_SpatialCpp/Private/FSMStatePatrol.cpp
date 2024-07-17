// Fill out your copyright notice in the Description page of Project Settings.

#include "FSMStatePatrol.h"
#include "MasterAiShooter.h"
#include "MasterAiController.h"
#include "NavigationSystem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"


UFSMStatePatrol::UFSMStatePatrol()
{
}

void UFSMStatePatrol::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Patrol State Entered"));

	MasterAiController = Cast<AMasterAiController>(GetOuter());
	AIShooter = Cast<AMasterAiShooter>(MasterAiController->GetPawn());

	if (!MasterAiController)
	{
		UE_LOG(LogTemp, Warning, TEXT("MasterAiController is not valid"));
	}
	if (!AIShooter)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIShooter is not valid"));
	}
	else
	{
		AIShooter->GetCharacterMovement()->MaxWalkSpeed = 250.f;
		MoveToNextPatrolLocation();
	}
}

void UFSMStatePatrol::Update(float DeltaTime)
{
	if (MasterAiController && AIShooter && !bIsWaiting && AIShooter->GetVelocity().IsNearlyZero())
	{
		if (FVector::Dist(PatrolLocation, AIShooter->GetActorLocation()) < 100.0f)
		{
			bIsWaiting = true;
			GetWorld()->GetTimerManager().SetTimer(WaitTimerHandle, this, &UFSMStatePatrol::OnWaitTimerEnd, AIShooter->GetPatrolTime(), false);
		}
	}
}

void UFSMStatePatrol::Exit()
{
	AIShooter->GetCharacterMovement()->MaxWalkSpeed = 600.f;

	UE_LOG(LogTemp, Warning, TEXT("Patrol State Exited"));
}

void UFSMStatePatrol::MoveToNextPatrolLocation()
{
	if (MasterAiController && AIShooter)
	{
		FVector CurrentLocation = AIShooter->GetActorLocation();
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIShooter->GetWorld());
		FNavLocation ResultLocation;

		if (NavSys->GetRandomPointInNavigableRadius(AIShooter->GetSpawnLocation(), AIShooter->GetPatrolRadius(), ResultLocation))
		{
			PatrolLocation = ResultLocation.Location;

			if (MasterAiController->MoveToLocation(PatrolLocation))
			{
				UE_LOG(LogTemp, Warning, TEXT("Moving to new location!"));
				bIsWaiting = false;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to move to new location!"));
				GetWorld()->GetTimerManager().SetTimer(WaitTimerHandle, this, &UFSMStatePatrol::MoveToNextPatrolLocation, 1.0f, false);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to get random point in navigable radius!"));
		}
	}
}

void UFSMStatePatrol::OnWaitTimerEnd()
{
	bIsWaiting = false;
	MoveToNextPatrolLocation();
}
