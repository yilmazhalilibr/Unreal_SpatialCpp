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

void UInventoryGridWidget::InitializeGrids(UInventorySubsystem* _inventorySubsystem, float _tileSize)
{
	// GRIDLER BASLAR VE PARAMETRELER ALINIR
	InventorySubsystem = _inventorySubsystem;
	TileSize = _tileSize;

	//GRÝD'ÝN BÜYÜKLÜÐÜ BELÝRLENÝR
	UCanvasPanelSlot* GridBorderSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
	GridBorderSlot->SetSize(FVector2D(InventorySubsystem->GetColumns() * TileSize, InventorySubsystem->GetRows() * TileSize));

	//GRID'ÝN KENARLARI ÇÝZÝLÝR
	CreateLineSegments();

}

void UInventoryGridWidget::CreateLineSegments()
{
	//GRID'ÝN KENARLARI ÇÝZÝLÝR VE LÝNES ARRAYINE EKLENÝR
	// 
	// DÝKEY ÇÝZGÝLER ÇÝZÝLÝR VE LÝNES ARRAYINE EKLENÝR
	for (int i = 0; i < InventorySubsystem->GetColumns(); i++)
	{
		float xlocal = TileSize * i;
		Lines.Add(FLine(FVector2D(xlocal, 0), FVector2D(xlocal, InventorySubsystem->GetRows() * TileSize)));
	}
	// YATAY ÇÝZGÝLER ÇÝZÝLÝR VE LÝNES ARRAYINE EKLENÝR
	for (int i = 0; i < InventorySubsystem->GetRows(); i++)
	{
		float ylocal = TileSize * i;
		Lines.Add(FLine(FVector2D(0, ylocal), FVector2D(InventorySubsystem->GetColumns() * TileSize, ylocal)));
	}



}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	//FOR loop ile Lines arrayindeki her bir eleman çizilir

	int32 CurrentLayer = LayerId;

	for (int32 i = 0; i < Lines.Num(); i += 2)
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
