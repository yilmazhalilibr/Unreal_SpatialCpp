#include "FSMStateChase.h"
#include "MasterAiShooter.h"
#include "MasterAiController.h"
#include "GameFramework/Character.h"
#include "AIController.h"

UFSMStateChase::UFSMStateChase()
{
}

void UFSMStateChase::Enter()
{
	MasterAiController = Cast<AMasterAiController>(GetOuter());
	if (MasterAiController)
	{
		Owner = Cast<AMasterAiShooter>(MasterAiController->GetPawn());
	}

	UE_LOG(LogTemp, Warning, TEXT("Entering Chase State"));

	if (MasterAiController && Owner)
	{
		FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		if (MasterAiController->MoveToLocation(PlayerLocation, Owner->GetChaseDistance()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Chasing the player"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to move to player location"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner or MasterAiController is not valid"));
		MasterAiController = Cast<AMasterAiController>(GetOuter());
		if (MasterAiController)
		{
			Owner = Cast<AMasterAiShooter>(MasterAiController->GetPawn());

		}
	}

}

void UFSMStateChase::Update(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Updating Chase State"));

	
}

void UFSMStateChase::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Chase State"));
}

AMasterAiShooter* UFSMStateChase::GetOwner() const
{
	return Owner;
}

AMasterAiController* UFSMStateChase::GetController() const
{
	return MasterAiController;
}
