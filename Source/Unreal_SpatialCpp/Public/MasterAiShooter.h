// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MasterAiShooter.generated.h"


class UFSMBase;
class UFSMStateIdle;
class UFSMStateWalk;
class UFSMStateRun;
class UFSMStateAttack;


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
	void ChangeStateBP(FString _state);

	UPROPERTY()
	UFSMStateIdle* IdleState;

	UPROPERTY()
	UFSMStateWalk* WalkState;

	UPROPERTY()
	UFSMStateRun* RunState;

	UPROPERTY()
	UFSMStateAttack* AttackState;

};
