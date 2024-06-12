// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryStructures.h"
#include "InventoryGridWidget.generated.h"

/**
 *
 */
class UInventorySubsystem;
class UCanvasPanel;
class UBorder;



UCLASS()
class UNREAL_SPATIALCPP_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeGrids(UInventorySubsystem* _inventorySubsystem, float _tileSize);

	UFUNCTION()
	void CreateLineSegments();

private:
	//bind canvas panel
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* GridCanvasPanel;

public:

	UPROPERTY()
	UInventorySubsystem* InventorySubsystem;

	UPROPERTY()
	float TileSize;

	UPROPERTY()
	float LineThickness = 1.0f;

	UPROPERTY()
	FLinearColor LineColor;


	UPROPERTY()
	TArray<FLine> Lines;

};
