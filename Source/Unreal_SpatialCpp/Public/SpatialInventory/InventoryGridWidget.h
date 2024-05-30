// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySubsystem.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "InventoryGridWidget.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	void OnPaint(FPaintContext& Context) const;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	UWidgetBlueprintLibrary* WidgetBlueprintLibraryInstance;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	UInventorySubsystem* InventorySubsystem;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	float TileSize;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FSLine> Lines;


private:
	void InitializeInventoryGridWidget();

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UBorder* GridBorder;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GridCanvasPanel;

	UFUNCTION()
	void CreateLineSegments();

public:

	void InitializeGrid(UInventorySubsystem inventorySubSystem, float tileSize);

};
