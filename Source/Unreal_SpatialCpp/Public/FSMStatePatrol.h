// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "FSMStatePatrol.generated.h"

/**
 *
 */

class AMasterAiShooter;
class AMasterAiController;

UCLASS()
class UNREAL_SPATIALCPP_API UFSMStatePatrol : public UFSMBase
{
	GENERATED_BODY()
public:
	UFSMStatePatrol();

	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;

private:
	UPROPERTY()
	AMasterAiShooter* AIShooter;

	UPROPERTY()
	AMasterAiController* MasterAiController;

	UPROPERTY()
	FVector PatrolLocation;

	UPROPERTY()
	bool bIsWaiting = false;

	FTimerHandle WaitTimerHandle;

	void MoveToNextPatrolLocation();
	void OnWaitTimerEnd();
};
