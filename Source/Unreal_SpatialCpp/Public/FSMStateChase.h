// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "FSMStateChase.generated.h"

/**
 *
 */


UCLASS()
class UNREAL_SPATIALCPP_API UFSMStateChase : public UFSMBase
{
	GENERATED_BODY()
public:
	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;

	AMasterAiShooter* GetOwner() const;

private:

	AMasterAiShooter* Owner;

};
