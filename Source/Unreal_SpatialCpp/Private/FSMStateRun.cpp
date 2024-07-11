#include "FSMStateRun.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

void UFSMStateRun::Enter()
{
    UE_LOG(LogTemp, Warning, TEXT("Entering Run State"));
}

void UFSMStateRun::Update(float DeltaTime)
{
    // Run state logic
    UE_LOG(LogTemp, Warning, TEXT("Updating Run State"));
}

void UFSMStateRun::Exit()
{
    UE_LOG(LogTemp, Warning, TEXT("Exiting Run State"));
}
