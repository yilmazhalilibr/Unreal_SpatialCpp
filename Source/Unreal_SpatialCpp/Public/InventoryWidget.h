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

	//Getter Inventory Grid Widget
	UFUNCTION(BlueprintCallable)
	UInventoryGridWidget* GetGrid() { return InventoryGrid; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UInventoryGridWidget* InventoryGrid;


protected:
	virtual void NativeConstruct() override;

	//Bind Canvas panel
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> BackgroundBorder;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> BackgroundBlur;





};
