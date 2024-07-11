#include "FSMStateWalk.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

void UFSMStateWalk::Enter()
{
    UE_LOG(LogTemp, Warning, TEXT("Entering Walk State"));
}

void UFSMStateWalk::Update(float DeltaTime)
{
    // Walk state logic
    UE_LOG(LogTemp, Warning, TEXT("Updating Walk State"));
}

void UFSMStateWalk::Exit()
{
    UE_LOG(LogTemp, Warning, TEXT("Exiting Walk State"));
}
