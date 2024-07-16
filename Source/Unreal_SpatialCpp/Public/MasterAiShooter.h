// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "MasterAiShooter.generated.h"







class AMasterAiController;
class UFSMBase;
class UFSMStateIdle;
class UFSMStateWalk;
class UFSMStateRun;
class UFSMStateAttack;
class UFSMStateChase;
class UFSMStateCover;


UENUM(BlueprintType)
enum class EState : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Chase,
	Cover
};


UCLASS()
class UNREAL_SPATIALCPP_API AMasterAiShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMasterAiShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// AI Properties
public:
	UFUNCTION(BlueprintCallable)
	float GetChaseDistance() const { return ChaseDistance; }

	UFUNCTION()
	float GetAttackDistance() const { return AttackDistance; }

	UFUNCTION()
	float GetMaxHP() const { return MaxHP; }

	UFUNCTION()
	float GetCurrentHP() const { return CurrentHP; }

	// AI Properties Getters
	UFUNCTION()
	float GetSightRadius() const { return SightRadius; }

	UFUNCTION()
	float GetSightLoseRadius() const { return SightLoseRadius; }

	UFUNCTION()
	float GetPeripheralVisionAngleDegrees() const { return PeripheralVisionAngleDegrees; }



public:
	UPROPERTY()
	FTimerHandle TimerHandle;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Properties")
	FText The_features_below_are_for_AI_Perception;
	/**AI Controller Properties*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float SightRadius = 3500.0f;

	/**AI Controller Properties (SightRadius + LoseRadius(Example:500.0f))*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float SightLoseRadius = 500.0f;

	/**AI Controller Properties*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float PeripheralVisionAngleDegrees = 120.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Properties")
	FText The_following_features_are_the_features_of_AI;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float ChaseDistance = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float AttackDistance = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float MaxHP = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float CurrentHP = 100.f;

};
