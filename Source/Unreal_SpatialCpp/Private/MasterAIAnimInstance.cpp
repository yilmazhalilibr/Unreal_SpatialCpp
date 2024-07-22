#include "MasterAIAnimInstance.h"
#include "MasterAiShooter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

void UMasterAIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Get the owner of the animation instance
	AIShooter = Cast<AMasterAiShooter>(TryGetPawnOwner());
}

void UMasterAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AIShooter)
	{
		MovementSpeed = AIShooter->GetVelocity().Size();
		bIsInAir = AIShooter->GetMovementComponent()->IsFalling();

		/*if (bIsAttacking && !Montage_IsPlaying(RifleFireMontage))
		{
			PlayAttackMontage();
		}*/
	}
}

void UMasterAIAnimInstance::PlayAttackMontage()
{
	if (AIShooter && RifleFireMontage)
	{
		// Play rifle montage
		Montage_Play(RifleFireMontage, 1.0f);
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Playing Attack Montage"));
		}
	}
}

void UMasterAIAnimInstance::SetAttack(bool _attacking)
{
	bIsAttacking = _attacking;
}
