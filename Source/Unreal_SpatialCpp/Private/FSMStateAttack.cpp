#include "FSMStateAttack.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "MasterAiController.h"
#include "MasterAiShooter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MasterAIAnimInstance.h"
#include "MasterAiSpawner.h"


UFSMStateAttack::UFSMStateAttack()
{

}

void UFSMStateAttack::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Attack State"));


	MasterAiController = Cast<AMasterAiController>(GetOuter());
	if (MasterAiController)
	{
		Owner = Cast<AMasterAiShooter>(MasterAiController->GetPawn());
		MasterAiSpawner = Cast<AMasterAiSpawner>(Owner->GetSpawner());
		//Stop all movement 
		MasterAiController->StopMovement();

		////AnimInstance will be added here
		//MasterAiAnimInstance = Cast<UMasterAIAnimInstance>(Owner->GetMesh()->GetAnimInstance());
		//MasterAiAnimInstance->SetAttack(true);
		////BURADA HATA VAR DUZELTILCEK

		OwnerAI = Cast<AALSBaseCharacter>(Owner);

		if (OwnerAI)
		{
			OwnerAI->SetOverlayState(EALSOverlayState::Rifle);
			OwnerAI->SetDesiredGait(EALSGait::Sprinting);

		}

	}


}

void UFSMStateAttack::Update(float DeltaTime)
{
	// Attack state logic
	//UE_LOG(LogTemp, Warning, TEXT("Updating Attack State"));

	EQSTimer += DeltaTime;

	if (MasterAiSpawner && EQSTimer > FMath::RandRange(5, 6))
	{
		EQSTimer = 0.0f;
		FVector AttackLocation = MasterAiSpawner->GetAttackCordinate(Owner);
		MasterAiController->MoveToLocation(AttackLocation);
		UE_LOG(LogTemp, Warning, TEXT("Attack Location: %s"), *AttackLocation.ToString());
	}

	if (Owner)
	{
		//Eðer ai duruyorsa focus atsýn
		if (Owner->GetCharacterMovement()->Velocity.Size() < 1.0f)
		{
			MasterAiController->SetFocus(GetWorld()->GetFirstPlayerController()->GetPawn());
			OwnerAI->SetRotationMode(EALSRotationMode::Aiming);

		}
		else
		{
			MasterAiController->SetFocus(nullptr);
		}
	}
	//Fire system will added here

}

void UFSMStateAttack::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Attack State"));
	//Clear focus
	MasterAiController->SetFocus(nullptr);

	OwnerAI = Cast<AALSBaseCharacter>(Owner);

	if (OwnerAI)
	{
		//OwnerAI->SetOverlayState(EALSOverlayState::Rifle);
		OwnerAI->SetRotationMode(EALSRotationMode::VelocityDirection);
		OwnerAI->SetDesiredGait(EALSGait::Running);

	}

	//MasterAiAnimInstance->SetAttack(false);

}

AMasterAiShooter* UFSMStateAttack::GetOwner() const
{
	return Owner;
}

AMasterAiController* UFSMStateAttack::GetController() const
{
	return MasterAiController;
}
//
//UMasterAIAnimInstance* UFSMStateAttack::GetMasterAiAnimInstance() const
//{
//	if (!MasterAiAnimInstance)
//	{
//		return MasterAiAnimInstance;
//	}
//
//	return nullptr;
//}