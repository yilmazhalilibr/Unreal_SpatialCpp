// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/InventoryGridWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"



void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateLineSegments();

}

void UInventoryGridWidget::NativeDestruct()
{
	Super::NativeDestruct();

}





int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{

	int32 CurrentLayer = LayerId;

	for (int32 i = 0; i < Lines.Num(); i++)
	{
		FVector2D Start = Lines[i].Start;
		FVector2D End = Lines[i].End;

		TArray<FVector2D> Points;
		Points.Add(Start);
		Points.Add(End);

		FSlateDrawElement::MakeLines(
			OutDrawElements,
			CurrentLayer,
			AllottedGeometry.ToPaintGeometry(),
			Points,
			ESlateDrawEffect::None,
			FLinearColor::Gray,
			true,
			1.0f
		);
	}


	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, CurrentLayer, InWidgetStyle, bParentEnabled);
}




void UInventoryGridWidget::CreateLineSegments()
{
	// GRID'ÝN KENARLARI ÇÝZÝLÝR VE LÝNES ARRAYINE EKLENÝR
	Lines.Empty();

	FVector2D TopLeft = FVector2D::ZeroVector;

	int32 Columns = 4;
	int32 Rows = 9;

	UE_LOG(LogTemp, Warning, TEXT("Columns: %d, Rows: %d"), Columns, Rows);

	if (GridBorder)
	{
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot))
		{
			TopLeft = CanvasSlot->GetPosition();
		}
	}

	for (int32 i = 0; i <= Columns; ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Topleft: %f"), TopLeft.X);
		float X = TopLeft.X + i * 50/*TÝLESIZE*/;
		Lines.Add(FLine(FVector2D(X, (float)TopLeft.Y), FVector2D(X, TopLeft.Y + Rows * 50/*TÝLESIZE*/)));
	}

	for (int32 j = 0; j <= Rows; ++j)
	{
		float Y = TopLeft.Y + j * 50/*TÝLESIZE*/;
		Lines.Add(FLine(FVector2D((float)TopLeft.X, Y), FVector2D(TopLeft.X + Columns * 50/*TÝLESIZE*/, Y)));
	}

	// Trigger a repaint
	Invalidate(EInvalidateWidgetReason::Paint);
}