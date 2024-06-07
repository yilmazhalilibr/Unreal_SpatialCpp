// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/InventoryUW.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/World.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SpatialInventory/ItemObject.h"


void UInventoryUW::NativeConstruct()
{
	Super::NativeConstruct();


	if (GridBorder && GridCanvasPanel)
	{
		FVector2D Size(Column * TileSize, Row * TileSize);
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot))
		{
			CanvasSlot->SetSize(Size);
		}
		CreateLineSegments();
	}
}


void UInventoryUW::CreateLineSegments()
{
	LineSegments.Empty();

	FVector2D TopLeft = FVector2D::ZeroVector;


	if (GridBorder)
	{
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot))
		{
			TopLeft = CanvasSlot->GetPosition();
		}
	}

	for (int32 i = 0; i <= Column; ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Topleft: %f"), TopLeft.X);
		float X = TopLeft.X + i * TileSize;
		LineSegments.Add(FVector2D(X, TopLeft.Y));
		LineSegments.Add(FVector2D(X, TopLeft.Y + Row * TileSize));
	}

	for (int32 j = 0; j <= Row; ++j)
	{
		float Y = TopLeft.Y + j * TileSize;
		LineSegments.Add(FVector2D(TopLeft.X, Y));
		LineSegments.Add(FVector2D(TopLeft.X + Column * TileSize, Y));
	}

	// Widget'�n yeniden �izilmesini tetiklemek i�in
	Invalidate(EInvalidateWidgetReason::Paint);
}


int32 UInventoryUW::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 CurrentLayer = LayerId;

	for (int32 i = 0; i < LineSegments.Num(); i += 2)
	{
		FVector2D Start = LineSegments[i];
		FVector2D End = LineSegments[i + 1];
		TArray<FVector2D> Points;
		Points.Add(Start);
		Points.Add(End);
		FSlateDrawElement::MakeLines(
			OutDrawElements,
			CurrentLayer,
			AllottedGeometry.ToPaintGeometry(),
			Points,
			ESlateDrawEffect::None,
			LineColor,
			true,
			LineTickness
		);
	}

	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, CurrentLayer, InWidgetStyle, bParentEnabled);
}





TArray<UItemObject*> UInventoryUW::GetAllItems()
{
	//ItemObject
	//TArray<UItemObject>


	return TArray<UItemObject*>();
}

void UInventoryUW::Refresh()
{
	GridCanvasPanel->ClearChildren();
}
