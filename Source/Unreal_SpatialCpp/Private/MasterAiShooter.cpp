// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterAiShooter.h"
#include "MasterAiController.h"
#include <Kismet/GameplayStatics.h>




AMasterAiShooter::AMasterAiShooter() : CurrentHP(MaxHP), AIDead(false)
{
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AMasterAiShooter::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();

	MasterAiController = Cast<AMasterAiController>(GetController());

	//Anydamage event
	OnTakeAnyDamage.AddDynamic(this, &AMasterAiShooter::OnTakeAIAnyDamage);
}

void AMasterAiShooter::Destroyed()
{
	Super::Destroyed();

	OnTakeAnyDamage.RemoveDynamic(this, &AMasterAiShooter::OnTakeAIAnyDamage);
}

// Called every frame
void AMasterAiShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMasterAiShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



void AMasterAiShooter::OnTakeAIAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//DamageCauser cast to player pawn

	if (DamageCauser->Tags.Contains("Player"))
	{
		DealDamage(Damage);

		if (MasterAiController)
		{
			MasterAiController->SetOnWarMode(true);
		}
	}

}

void AMasterAiShooter::DealDamage(float Damage)
{
	CurrentHP -= Damage;

	if (CurrentHP <= 0)
	{
		AIDead = true;
		OnAiDead.Broadcast(this, AIDead);
	}
}



