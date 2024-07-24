// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "FSMStateAttack.generated.h"

/**
 *
 */

class AMasterAiShooter;
class AMasterAiController;
class UMasterAIAnimInstance;
class AMasterAiSpawner;


UCLASS()
class UNREAL_SPATIALCPP_API UFSMStateAttack : public UFSMBase
{
	GENERATED_BODY()

public:
	UFSMStateAttack();

	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;

	AMasterAiShooter* GetOwner() const;

	AMasterAiController* GetController() const;

	UMasterAIAnimInstance* GetMasterAiAnimInstance() const;

	void SetController(AMasterAiController* _controller) { MasterAiController = _controller; }

	UPROPERTY()
	AMasterAiSpawner* MasterAiSpawner;

	UPROPERTY()
	float EQSTimer;

private:
	UPROPERTY()
	UMasterAIAnimInstance* MasterAiAnimInstance;

	UPROPERTY()
	AMasterAiShooter* Owner;

	UPROPERTY()
	AMasterAiController* MasterAiController;
};
