#include "FSMStateHeard.h"
#include "MasterAiShooter.h"
#include "MasterAiController.h"
#include "GameFramework/CharacterMovementComponent.h"

UFSMStateHeard::UFSMStateHeard()
{

}

void UFSMStateHeard::Enter()
{
    UE_LOG(LogTemp, Warning, TEXT("Heard State Entered"));

    MasterAiController = Cast<AMasterAiController>(GetOuter());
    if (MasterAiController)
    {
        AIShooter = Cast<AMasterAiShooter>(MasterAiController->GetPawn());

        // Look at Last Known Location
        if (AIShooter)
        {
            AIShooter->GetCharacterMovement()->StopActiveMovement();
            AIShooter->GetCharacterMovement()->MaxWalkSpeed = 250.0f;

            // Set initial look at rotation
            LookAtRotation = FRotationMatrix::MakeFromX(MasterAiController->GetLastHeardLocation() - AIShooter->GetActorLocation()).Rotator();
        }
    }
}

void UFSMStateHeard::Update(float DeltaTime)
{
    if (MasterAiController && AIShooter)
    {
        // Smoothly rotate towards the last heard location
        AIShooter->SetActorRotation(FMath::RInterpTo(AIShooter->GetActorRotation(), LookAtRotation, DeltaTime, 2.0f));

        // If the rotation is nearly complete, move to the last heard location
        if (FMath::IsNearlyEqual(AIShooter->GetActorRotation().Yaw, LookAtRotation.Yaw, 1.0f))
        {
            MasterAiController->MoveToLocation(MasterAiController->GetLastHeardLocation());
        }
    }
}

void UFSMStateHeard::Exit()
{
    UE_LOG(LogTemp, Warning, TEXT("Heard State Exit"));

    if (AIShooter)
    {
        AIShooter->GetCharacterMovement()->StopActiveMovement();
        AIShooter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    }

    if (MasterAiController)
    {
        MasterAiController->SetIsPlayerHeard(false);
        //Clear focus
		MasterAiController->ClearFocus(EAIFocusPriority::Gameplay);
    }
}
