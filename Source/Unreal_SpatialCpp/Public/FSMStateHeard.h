// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "FSMStateHeard.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API UFSMStateHeard : public UFSMBase
{
	GENERATED_BODY()

public:
	UFSMStateHeard();

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float DeltaTime) override;

private:
	UPROPERTY()
	class AMasterAiShooter* AIShooter;

	UPROPERTY()
	class AMasterAiController* MasterAiController;

	UPROPERTY()
	FRotator LookAtRotation;



};
