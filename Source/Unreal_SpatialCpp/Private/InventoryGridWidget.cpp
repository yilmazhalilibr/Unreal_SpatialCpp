// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"
#include "InventorySubsystem.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "ItemWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryWidget.h"

#include "ItemObject.h"


void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Inventorysubsystem'i gameInstance dan �ekmek i�in kullan�l�r
	InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
}

void UInventoryGridWidget::NativeDestruct()
{

	Super::NativeDestruct();

	InventorySubsystem->OnInventoryChanged.RemoveDynamic(this, &UInventoryGridWidget::Refresh);

}

void UInventoryGridWidget::InitializeGrids(UInventoryWidget* _inventoryWidget)
{
	BPItemWidget = _inventoryWidget->GetItemWidget();

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

		//GR�D'�N B�Y�KL��� BEL�RLEN�R
		UCanvasPanelSlot* GridBorderSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
		GridBorderSlot->SetSize(FVector2D(InventorySubsystem->GetColumns() * TileSize, InventorySubsystem->GetRows() * TileSize));

		//GRID'�N KENARLARI ��Z�L�R
		CreateLineSegments();
		//GRID'�N ���N� DOLDURMAK ���N REFRESH FONKS�YONU �A�IRILIR
		Refresh();


		//Bind event OnInventoryChanged
		InventorySubsystem->OnInventoryChanged.AddDynamic(this, &UInventoryGridWidget::Refresh);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GridBorder is not bound.(GRID-WIDGET)"));

	}
}

void UInventoryGridWidget::CreateLineSegments()
{
	//GRID'�N KENARLARI ��Z�L�R VE L�NES ARRAYINE EKLEN�R
	// 
	// D�KEY ��ZG�LER ��Z�L�R VE L�NES ARRAYINE EKLEN�R
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

void UInventoryGridWidget::Refresh()
{
	//GRID TEM�ZLEN�R
	GridCanvasPanel->ClearChildren();

	if (!InventorySubsystem)
	{
		InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	}

	//T�M �TEMLAR ALINIR
	TMap<AItemObject*, FTile> _items;
	InventorySubsystem->GetAllItems(_items);

	//Her bir item'i ve tile'i bir for loop ile �izilir
	for (auto& Item : _items)
	{
		AItemObject* _itemObject = Item.Key;
		FTile _topLeftTile = Item.Value;

		//Create a new item widget

		auto _itemWidget = Cast<UItemWidget>(CreateWidget(GetWorld(), BPItemWidget));

		/*UMaterialInterface* _icon;
		_itemObject->GetIcon(_icon);*/

		_itemWidget->InitializeWidget(_itemObject, TileSize);


		//Bind event FRemoved
		_itemWidget->OnRemoved.AddDynamic(this, &UInventoryGridWidget::OnItemRemoved);

		//Set the size of the item widget
		auto slot = GridCanvasPanel->AddChild(_itemWidget);

		//cast to canvaspanelslot to slot
		if (UCanvasPanelSlot* _canvasSlotCast = Cast<UCanvasPanelSlot>(slot))
		{
			_canvasSlotCast->SetAutoSize(true);
			_canvasSlotCast->SetPosition(FVector2D(_topLeftTile.X * TileSize, _topLeftTile.Y * TileSize));


		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CanvasSlot is not casted"));
		}

	}


}

void UInventoryGridWidget::OnItemRemoved(AItemObject* _itemObject)
{
	//Item silinir
	InventorySubsystem->RemoveItem(_itemObject);
	//Refresh();
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	//FOR loop ile Lines arrayindeki her bir eleman �izilir

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


