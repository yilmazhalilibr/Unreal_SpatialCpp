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


UENUM(BlueprintType)
enum class EState : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Chase
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


private:
	UFSMBase* CurrentState;


	UFUNCTION()
	void ChangeState(UFSMBase* NewState);

	UFUNCTION(BlueprintCallable)
	void ChangeStateBP(EState _state);

	UPROPERTY()
	UFSMStateIdle* IdleState;

	UPROPERTY()
	UFSMStateWalk* WalkState;

	UPROPERTY()
	UFSMStateRun* RunState;

	UPROPERTY()
	UFSMStateAttack* AttackState;

	UPROPERTY()
	UFSMStateChase* ChaseState;


	// AI Properties
public:
	UFUNCTION(BlueprintCallable)
	float GetChaseDistance() const { return ChaseDistance; }

	UFUNCTION()
	void SetPerceptionProperties(float& _sightRadius, float& _sightLoseRadius, float& _peripheralVisionAngleDegrees);

private:
	UPROPERTY()
	AMasterAiController* MasterAiController;

public:
	UPROPERTY()
	FTimerHandle TimerHandle;

	/**AI Controller Properties*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float SightRadius = 3500.0f;

	/**AI Controller Properties (SightRadius + LoseRadius(Example:500.0f))*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float SightLoseRadius = 500.0f;

	/**AI Controller Properties*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float PeripheralVisionAngleDegrees = 120.0f;

	UPROPERTY(EditAnywhere, Category = "AI Properties")
	float ChaseDistance = 150.f;

};
