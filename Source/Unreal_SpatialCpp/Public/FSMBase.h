// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterAiShooter.h"
#include "UObject/NoExportTypes.h"
#include "FSMBase.generated.h"

/**
 *
 */



UCLASS()
class UNREAL_SPATIALCPP_API UFSMBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Enter() PURE_VIRTUAL(UFSMBase::Enter, );
	virtual void Update(float DeltaTime) PURE_VIRTUAL(UFSMBase::Update, );
	virtual void Exit() PURE_VIRTUAL(UFSMBase::Exit, );



};
