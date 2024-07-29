// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "FSMStateChase.generated.h"

/**
 *
 */

class AMasterAiShooter;
class AMasterAiController;
class AMasterAiSpawner;


UCLASS()
class UNREAL_SPATIALCPP_API UFSMStateChase : public UFSMBase
{
	GENERATED_BODY()
public:

	//Constructor
	UFSMStateChase();

	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;

	AMasterAiShooter* GetOwner() const;

	AMasterAiController* GetController() const;

	void SetController(AMasterAiController* _controller) { MasterAiController = _controller; }

	float ChaseTimer;


private:
	UPROPERTY()
	AMasterAiSpawner* MasterAiSpawner;

	UPROPERTY()
	AMasterAiShooter* Owner;
	UPROPERTY()
	AMasterAiController* MasterAiController;
	UPROPERTY()
	AALSBaseCharacter* ALSCharacter;

};
