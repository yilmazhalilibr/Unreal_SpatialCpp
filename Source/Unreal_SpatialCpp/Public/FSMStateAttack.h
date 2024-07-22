// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "FSMStateAttack.generated.h"

/**
 *
 */

class AMasterAiShooter;
class AMasterAiController;
class UMasterAIAnimInstance;


UCLASS()
class UNREAL_SPATIALCPP_API UFSMStateAttack : public UFSMBase
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;

	AMasterAiShooter* GetOwner() const;

	AMasterAiController* GetController() const;

	UMasterAIAnimInstance* GetMasterAiAnimInstance() const;

	void SetController(AMasterAiController* _controller) { MasterAiController = _controller; }

private:

	UMasterAIAnimInstance* MasterAiAnimInstance;

	AMasterAiShooter* Owner;

	AMasterAiController* MasterAiController;
};
