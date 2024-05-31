// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUW.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API UInventoryUW : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FLinearColor LineColor; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float LineTickness;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CreateLineSegments();

protected:
	virtual void NativeConstruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

private:
	UPROPERTY(meta = (BindWidget))
	class UBorder* GridBorder;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GridCanvasPanel;

	TArray<FVector2D> LineSegments;

};
