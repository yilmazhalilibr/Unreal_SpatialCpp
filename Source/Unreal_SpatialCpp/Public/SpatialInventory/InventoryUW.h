#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "ItemUW.h"
#include "InventorySubsystem.h"
#include "InventoryUW.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API UInventoryUW : public UUserWidget
{
    GENERATED_BODY()

public:
    UInventoryUW();

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
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
    bool IsPointOnLineSegment(const FVector2D& Point, const FVector2D& LineStart, const FVector2D& LineEnd);
    void AddItemToGrid(const FVector2D& Position);
    void RemoveItemFromGrid(UItemUW* ItemWidget);

    UPROPERTY(meta = (BindWidget))
    UBorder* GridBorder;

    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* GridCanvasPanel;

    UPROPERTY()
    TArray<FVector2D> LineSegments;

    UPROPERTY()
    UInventorySubsystem* InventorySubsystem;

    UPROPERTY()
    TMap<FVector2D, UItemUW*> ItemWidgets;  // Segment pozisyonlarýna göre item widget'larýný saklar
};
