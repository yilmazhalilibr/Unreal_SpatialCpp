// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 *
 */


UCLASS()
class UNREAL_SPATIALCPP_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* BackgroundSB;

	UPROPERTY(meta = (BindWidget))
	class UBorder* BackgroundBorder;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;
};
