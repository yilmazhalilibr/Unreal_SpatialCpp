// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMStateChase.h"
#include "MasterAiShooter.h"
#include "AIController.h"



void UFSMStateChase::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Chase State"));


}

void UFSMStateChase::Update(float DeltaTime)
{
	// Run state logic
	UE_LOG(LogTemp, Warning, TEXT("Updating Chase State"));

	if (GetOwner())
	{
		//UE_LOG(LogTemp, Warning, TEXT("GetOwner State"));

		auto* _controller = Cast<AAIController>(GetOwner()->GetController());
		if (_controller)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Chase"));

			if (_controller->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), GetOwner()->GetChaseDistance()))
			{
				UE_LOG(LogTemp, Warning, TEXT("Chase"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Stop Chase"));
			}

		}
	}


}

void UFSMStateChase::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Chase State"));
}

AMasterAiShooter* UFSMStateChase::GetOwner() const
{
	return Cast<AMasterAiShooter>(GetOuter());

}
