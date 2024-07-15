// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "FSMStateCover.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_SPATIALCPP_API UFSMStateCover : public UFSMBase
{
	GENERATED_BODY()

	UFSMStateCover();

public:
	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;



};
