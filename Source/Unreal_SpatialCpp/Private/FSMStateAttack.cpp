#include "FSMStateAttack.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "MasterAiController.h"
#include "MasterAiShooter.h"

void UFSMStateAttack::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Attack State"));

	MasterAiController = Cast<AMasterAiController>(GetOuter());
	if (MasterAiController)
	{
		Owner = Cast<AMasterAiShooter>(MasterAiController->GetPawn());
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
}

AMasterAiShooter* UFSMStateAttack::GetOwner() const
{
	return Owner;
}

AMasterAiController* UFSMStateAttack::GetController() const
{
	return MasterAiController;
}