// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterAiShooter.h"
#include "MasterAiController.h"



AMasterAiShooter::AMasterAiShooter()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMasterAiShooter::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();
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



