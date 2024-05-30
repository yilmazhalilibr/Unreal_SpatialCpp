// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	void InitializeInventoryWidget();

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UBorder* BackgroundBorder;

	UPROPERTY(meta = (BindWidget))
	class UBackgroundBlur* BackgroundBlur;

	UPROPERTY(meta = (BindWidget))
	class UInventoryGridWidget* InventoryGridWidget;
};
