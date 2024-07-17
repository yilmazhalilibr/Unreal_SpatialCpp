// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"

#include "FSMStateSearch.generated.h"

/**
 *
 */
class AMasterAiShooter;
class AMasterAiController;


UCLASS()
class UNREAL_SPATIALCPP_API UFSMStateSearch : public UFSMBase
{
	GENERATED_BODY()
public:
	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;

	UFUNCTION()
	FVector GetSearchLocation() { return SearchLocation; }

	UFUNCTION()
	void SetSearchLocation(FVector Location) { SearchLocation = Location; }

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	UPROPERTY()
	FTimerHandle LookAtTimerHandle;

private:
	UPROPERTY()
	AMasterAiShooter* AIShooter;

	UPROPERTY()
	AMasterAiController* MasterAiController;

	UPROPERTY()
	FVector SearchLocation;

};
