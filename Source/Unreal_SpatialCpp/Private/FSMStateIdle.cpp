// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMStateIdle.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

UFSMStateIdle::UFSMStateIdle()
{

}

void UFSMStateIdle::Enter()
{
    UE_LOG(LogTemp, Warning, TEXT("Entering Idle State"));
}

void UFSMStateIdle::Update(float DeltaTime)
{
    // Idle state logic
    //UE_LOG(LogTemp, Warning, TEXT("Updating Idle State"));
}

void UFSMStateIdle::Exit()
{
    UE_LOG(LogTemp, Warning, TEXT("Exiting Idle State"));
}