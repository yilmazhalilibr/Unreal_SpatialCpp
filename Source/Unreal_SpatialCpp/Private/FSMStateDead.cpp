// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMStateDead.h"
#include "MasterAiController.h"
#include "MasterAiShooter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFSMStateDead::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Dead State Enter"));

	MasterAiController = Cast<AMasterAiController>(GetOuter());
	AIShooter = Cast<AMasterAiShooter>(MasterAiController->GetPawn());


	//Open physics simulation
	AIShooter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	AIShooter->GetMesh()->SetSimulatePhysics(true);
	AIShooter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// 5 seconds after death, destroy the AI in Exit function use Lambda 
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			Exit();
		}, AIShooter->GetDeadDestroyTime(), false);
}

void UFSMStateDead::Update(float DeltaTime)
{

}

void UFSMStateDead::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Dead State Exit"));

	AIShooter->Destroy();

}
