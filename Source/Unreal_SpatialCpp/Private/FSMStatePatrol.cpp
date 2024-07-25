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
		UE_LOG(LogTemp, Error, TEXT("MasterAiController is not valid"));
		return;
	}
	if (!AIShooter)
	{
		UE_LOG(LogTemp, Error, TEXT("AIShooter is not valid"));
		return;
	}

	AIShooter->GetCharacterMovement()->MaxWalkSpeed = 250.f;
	MoveToNextPatrolLocation();
}

void UFSMStatePatrol::Update(float DeltaTime)
{
	if (!MasterAiController || !AIShooter)
	{
		return;
	}

	if (!bIsWaiting && AIShooter->GetVelocity().IsNearlyZero())
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
	if (!AIShooter)
	{
		UE_LOG(LogTemp, Error, TEXT("AIShooter is not valid"));
		return;
	}

	AIShooter->GetCharacterMovement()->MaxWalkSpeed = 600.f;

	UE_LOG(LogTemp, Warning, TEXT("Patrol State Exited"));
}

void UFSMStatePatrol::MoveToNextPatrolLocation()
{
	if (!MasterAiController || !AIShooter)
	{
		UE_LOG(LogTemp, Error, TEXT("MasterAiController or AIShooter is not valid"));
		return;
	}

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
			UE_LOG(LogTemp, Error, TEXT("Failed to move to new location!"));
			GetWorld()->GetTimerManager().SetTimer(MoveRetryTimerHandle, this, &UFSMStatePatrol::MoveToNextPatrolLocation, 1.0f, false);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get random point in navigable radius!"));
		GetWorld()->GetTimerManager().SetTimer(MoveRetryTimerHandle, this, &UFSMStatePatrol::MoveToNextPatrolLocation, 1.0f, false);
	}
}

void UFSMStatePatrol::OnWaitTimerEnd()
{
	bIsWaiting = false;
	MoveToNextPatrolLocation();
}
