// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "FSMStateResetAI.generated.h"

/**
 * 
 */

class AMasterAiShooter;
class AMasterAiController;


UCLASS()
class UNREAL_SPATIALCPP_API UFSMStateResetAI : public UFSMBase
{
	GENERATED_BODY()
	
public:
	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;

	//Getters setters in private variables
	UFUNCTION()
	void SetAIShooter(AMasterAiShooter* InAIShooter) { AIShooter = InAIShooter; }
	UFUNCTION()
	void SetMasterAiController(AMasterAiController* InMasterAiController) { MasterAiController = InMasterAiController; }

	UFUNCTION()
	AMasterAiShooter* GetAIShooter() { return AIShooter; }
	UFUNCTION()
	AMasterAiController* GetMasterAiController() { return MasterAiController; }

private:
	UPROPERTY()
	AMasterAiShooter* AIShooter;

	UPROPERTY()
	AMasterAiController* MasterAiController;


};
