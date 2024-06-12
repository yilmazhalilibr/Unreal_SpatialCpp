// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryStructures.h"
#include "InventoryWidget.generated.h"

/**
 *
 */

class UCanvasPanel;
class UBorder;
class UBackgroundBlur;
class UInventoryGridWidget;
class UInventorySubsystem;

UCLASS()
class UNREAL_SPATIALCPP_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	//Event On Initialized Widget
	virtual void NativeOnInitialized() override;

public:

	UPROPERTY()
	UInventorySubsystem* InventorySubsystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	FLinearColor LineColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	float LineThickness = 1.0f;

	//Getter Inventory Grid Widget
	UFUNCTION(BlueprintCallable)
	UInventoryGridWidget* GetGrid() { return InventoryGrid; }

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UInventoryGridWidget* InventoryGrid;  // UInventoryGridWidget türünü kullanýn
private:

	//Bind Canvas panel
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;





};
