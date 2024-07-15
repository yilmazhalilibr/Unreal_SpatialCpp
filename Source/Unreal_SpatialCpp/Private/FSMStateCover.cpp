// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMStateCover.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

UFSMStateCover::UFSMStateCover()
{

}

void UFSMStateCover::Enter()
{
    UE_LOG(LogTemp, Warning, TEXT("Entering UFSMStateCover State"));
}

void UFSMStateCover::Update(float DeltaTime)
{
    // Idle state logic
    //UE_LOG(LogTemp, Warning, TEXT("Updating UFSMStateCover State"));
}

void UFSMStateCover::Exit()
{
    UE_LOG(LogTemp, Warning, TEXT("Exiting UFSMStateCover State"));
}


