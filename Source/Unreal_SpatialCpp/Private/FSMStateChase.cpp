// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMStateChase.h"

void UFSMStateChase::Enter()
{
    UE_LOG(LogTemp, Warning, TEXT("Entering Run State"));


}

void UFSMStateChase::Update(float DeltaTime)
{
    // Run state logic
    UE_LOG(LogTemp, Warning, TEXT("Updating Run State"));

    

}

void UFSMStateChase::Exit()
{
    UE_LOG(LogTemp, Warning, TEXT("Exiting Run State"));
}