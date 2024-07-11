#include "FSMStateAttack.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

void UFSMStateAttack::Enter()
{
    UE_LOG(LogTemp, Warning, TEXT("Entering Attack State"));
}

void UFSMStateAttack::Update(float DeltaTime)
{
    // Attack state logic
    UE_LOG(LogTemp, Warning, TEXT("Updating Attack State"));
}

void UFSMStateAttack::Exit()
{
    UE_LOG(LogTemp, Warning, TEXT("Exiting Attack State"));
}
