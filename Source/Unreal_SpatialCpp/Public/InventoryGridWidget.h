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
class UCanvasPanelSlot;
class UItemWidget;
class UItemObject;
class UItem;
class UInventoryWidget;
class AItemObject;
class UDragDropOperation;




UCLASS()
class UNREAL_SPATIALCPP_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	//Descructor
	virtual void NativeDestruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//OnDragOver
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


	UPROPERTY()
	TSubclassOf<UItemWidget> BPItemWidget;


public:

	UFUNCTION(BlueprintCallable)
	void InitializeGrids(UInventoryWidget* _inventoryWidget);

	UFUNCTION()
	void CreateLineSegments();

	UFUNCTION()
	bool IsRoomAvailableForPayload(AItemObject* _payload);

	UFUNCTION()
	void Refresh();

private:

	UFUNCTION()
	AItemObject* GetPayload(UDragDropOperation* _dragDropOperation);

	//bind canvas panel
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* GridCanvasPanel;

	UFUNCTION()
	void OnItemRemoved(AItemObject* _itemObject);

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

	UPROPERTY()
	TSubclassOf<AItemObject> BP_ItemObject;


	//crea Refresh Implementation function
	UFUNCTION(BlueprintImplementableEvent, Category = "InventoryGridWidget", meta = (DisplayName = "Refresh"))
	void Refresh_Implementation();


	//OnMouseButtonDownEvent for GridBorder
	UFUNCTION()
	void OnGridBorderMouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UPROPERTY()
	FIntPoint DraggedItemTopLeftTile;
	UPROPERTY()
	bool DrawDropLocation;

	UFUNCTION()
	void MousePositionInTile(FVector2D _mousePosition, bool& _right, bool& _down) const;

};
