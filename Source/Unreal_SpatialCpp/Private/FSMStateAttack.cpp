#include "FSMStateAttack.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "MasterAiController.h"
#include "MasterAiShooter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MasterAIAnimInstance.h"

void UFSMStateAttack::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Attack State"));

	MasterAiController = Cast<AMasterAiController>(GetOuter());
	if (MasterAiController)
	{
		Owner = Cast<AMasterAiShooter>(MasterAiController->GetPawn());
		//Owner->GetCharacterMovement()->StopMovementImmediately();

		//AnimInstance will be added here
		MasterAiAnimInstance = Cast<UMasterAIAnimInstance>(Owner->GetMesh()->GetAnimInstance());
		MasterAiAnimInstance->SetAttack(true);
	}


}

void UFSMStateAttack::Update(float DeltaTime)
{
	// Attack state logic
	UE_LOG(LogTemp, Warning, TEXT("Updating Attack State"));

	MasterAiController->SetFocus(GetWorld()->GetFirstPlayerController()->GetPawn());
	//Fire system will added here

}

void UFSMStateAttack::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Attack State"));
	//Clear focus
	MasterAiController->SetFocus(nullptr);
	MasterAiAnimInstance->SetAttack(false);

}

AMasterAiShooter* UFSMStateAttack::GetOwner() const
{
	return Owner;
}

AMasterAiController* UFSMStateAttack::GetController() const
{
	return MasterAiController;
}

UMasterAIAnimInstance* UFSMStateAttack::GetMasterAiAnimInstance() const
{
	if (!MasterAiAnimInstance)
	{
		return MasterAiAnimInstance;
	}

	return nullptr;
}
