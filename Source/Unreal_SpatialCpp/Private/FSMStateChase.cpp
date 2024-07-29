#include "FSMStateChase.h"
#include "MasterAiShooter.h"
#include "MasterAiController.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "MasterAiSpawner.h"
#include "GameFramework/CharacterMovementComponent.h"


UFSMStateChase::UFSMStateChase()
{
}

void UFSMStateChase::Enter()
{
	if (!MasterAiController || !Owner)
	{
		MasterAiController = Cast<AMasterAiController>(GetOuter());

		if (MasterAiController)
		{
			Owner = Cast<AMasterAiShooter>(MasterAiController->GetPawn());
			MasterAiSpawner = Cast<AMasterAiSpawner>(Owner->GetSpawner());

			ALSCharacter = Cast<AALSBaseCharacter>(Owner);

			ALSCharacter->SetDesiredGait(EALSGait::Sprinting);
		}

	}

	UE_LOG(LogTemp, Warning, TEXT("Entering Chase State"));


	//if (MasterAiController && Owner)
	//{
	//	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	//	if (MasterAiController->MoveToLocation(PlayerLocation, Owner->GetChaseDistance()))
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Chasing the player"));
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Failed to move to player location"));
	//	}
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Owner or MasterAiController is not valid"));
	//	MasterAiController = Cast<AMasterAiController>(GetOuter());
	//	if (MasterAiController)
	//	{
	//		Owner = Cast<AMasterAiShooter>(MasterAiController->GetPawn());

	//	}
	//}

}

void UFSMStateChase::Update(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Updating Chase State"));

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	/*if (!MasterAiController->OnWarMode)
	{
		ChaseTimer += DeltaTime;
	}
	if (!MasterAiController->OnWarMode && ChaseTimer > Owner->GetSuspicionTime())
	{
		MasterAiController->SetOnWarMode(true);
		MasterAiSpawner->WarningPlayerDetected(true);
		ChaseTimer = 0.0f;
	}*/



	if (MasterAiSpawner && MasterAiController->MoveToLocation(PlayerLocation, Owner->GetChaseDistance()) && MasterAiController->OnWarMode)
	{
		FVector AttackLocation = MasterAiSpawner->GetAttackCordinate(Owner);
		MasterAiController->MoveToLocation(AttackLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Chase Location: %s"), *AttackLocation.ToString());


		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				//Set focus player if velocity equals 0
				if (Owner->GetCharacterMovement()->Velocity.Size() < 1.0f)
				{
					MasterAiController->SetFocus(GetWorld()->GetFirstPlayerController()->GetPawn());
				}
				else
				{
					MasterAiController->SetFocus(nullptr);
				}

			}, 1.0f, false);

	}
	else
	{
		if (MasterAiController && Owner)
		{

			if (MasterAiController->MoveToLocation(PlayerLocation, Owner->GetChaseDistance()))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Chasing the player"));
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("Failed to move to player location"));
			}
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Owner or MasterAiController is not valid"));
			MasterAiController = Cast<AMasterAiController>(GetOuter());
			if (MasterAiController)
			{
				Owner = Cast<AMasterAiShooter>(MasterAiController->GetPawn());

			}
		}
	}

}

void UFSMStateChase::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Chase State"));
	//Clear focus
	ALSCharacter->SetDesiredGait(EALSGait::Running);


}

AMasterAiShooter* UFSMStateChase::GetOwner() const
{
	return Owner;
}

AMasterAiController* UFSMStateChase::GetController() const
{
	return MasterAiController;
}
