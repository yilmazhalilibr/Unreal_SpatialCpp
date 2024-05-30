// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Styling/SlateBrush.h"
#include "SBColor.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API USBColor : public UObject
{
	GENERATED_BODY()

	//constructor
public:
	USBColor();

	//Create UPROPERTY FSlateBrush for the color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brush")
	FSlateBrush Brush;

};
