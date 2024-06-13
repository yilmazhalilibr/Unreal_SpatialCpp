// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"
#include "InventorySubsystem.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Inventorysubsystem'i gameInstance dan çekmek için kullanýlýr
	InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
}

void UInventoryGridWidget::InitializeGrids()
{
	// GRIDLER BASLAR VE PARAMETRELER ALINIR
	if (InventorySubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventorySubsystem found."));
	}
	else
	{
		return;
	}

	TileSize = InventorySubsystem->GetTileSize();
	LineColor = InventorySubsystem->GetLineColor();
	LineThickness = InventorySubsystem->GetLineThickness();

	if (GridBorder)
	{

		//GRÝD'ÝN BÜYÜKLÜÐÜ BELÝRLENÝR
		UCanvasPanelSlot* GridBorderSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
		GridBorderSlot->SetSize(FVector2D(InventorySubsystem->GetColumns() * TileSize, InventorySubsystem->GetRows() * TileSize));

		//GRID'ÝN KENARLARI ÇÝZÝLÝR
		CreateLineSegments();

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GridBorder is not bound.(GRID-WIDGET)"));

	}
}

void UInventoryGridWidget::CreateLineSegments()
{
	//GRID'ÝN KENARLARI ÇÝZÝLÝR VE LÝNES ARRAYINE EKLENÝR
	// 
	// DÝKEY ÇÝZGÝLER ÇÝZÝLÝR VE LÝNES ARRAYINE EKLENÝR
	Lines.Empty();

	FVector2D TopLeft = FVector2D::ZeroVector;

	int32 Columns = InventorySubsystem->GetColumns();
	int32 Rows = InventorySubsystem->GetRows();

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
		float X = TopLeft.X + i * TileSize;
		Lines.Add(FLine(FVector2D(X, (float)TopLeft.Y), FVector2D(X, TopLeft.Y + Rows * TileSize)));
	}

	for (int32 j = 0; j <= Rows; ++j)
	{
		float Y = TopLeft.Y + j * TileSize;
		Lines.Add(FLine(FVector2D((float)TopLeft.X, Y), FVector2D(TopLeft.X + Columns * TileSize, Y)));
	}

	// Trigger a repaint
	Invalidate(EInvalidateWidgetReason::Paint);


}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	//FOR loop ile Lines arrayindeki her bir eleman çizilir

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
			LineColor,
			true,
			LineThickness
		);
	}

	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, CurrentLayer, InWidgetStyle, bParentEnabled);
}
