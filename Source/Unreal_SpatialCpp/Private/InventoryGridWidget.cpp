// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"
#include "InventorySubsystem.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "ItemWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryWidget.h"
#include "ItemObject.h"
#include "Blueprint/DragDropOperation.h"
#include "Input/DragAndDrop.h"
#include "Input/Events.h"
#include "Blueprint/UserWidget.h"


void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Inventorysubsystem'i gameInstance dan çekmek için kullanýlýr
	InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();

	GridBorder->OnMouseButtonDownEvent.BindUFunction(this, FName("OnGridBorderMouseDown"));

}

void UInventoryGridWidget::NativeDestruct()
{

	Super::NativeDestruct();

	InventorySubsystem->OnInventoryChanged.RemoveDynamic(this, &UInventoryGridWidget::Refresh);

	GridBorder->OnMouseButtonDownEvent.Unbind();

}


bool UInventoryGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	AItemObject* _payload = GetPayload(InOperation);

	if (_payload && IsRoomAvailableForPayload(_payload))
	{
		//_payload = GetPayload(InOperation);

		FTile _draggedItemTopLeftTile = FTile(DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y);
		int _index;

		InventorySubsystem->TileToIndex(_draggedItemTopLeftTile, _index);

		InventorySubsystem->RemoveItem(_payload);

		InventorySubsystem->AddItemAt(_payload, _index);

		Refresh();

		return true;
	}
	else
	{
		bool _isSuccess;
		InventorySubsystem->TryAddItem(_payload, _isSuccess);
		if (!_isSuccess)
		{
			InventorySubsystem->SpawnItemFromActor(_payload, GetOwningPlayer()->GetPawn(), true);
		}
		else
		{

		}

	}


	return false; // Indicate that we did not handle the drop
}

bool UInventoryGridWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	FVector2D MouseLocalPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetLastScreenSpacePosition());

	bool Right, Down;
	MousePositionInTile(MouseLocalPosition, Right, Down);

	AItemObject* ItemObject = Cast<AItemObject>(InOperation->Payload);
	if (!ItemObject)
	{
		return false;
	}

	FIntPoint Dimension = ItemObject->GetDimensions();
	if (Right)
	{
		Dimension.X = FMath::Max(0, Dimension.X - 1);
	}
	if (Down)
	{
		Dimension.Y = FMath::Max(0, Dimension.Y - 1);
	}

	FVector2D MousePosInTile = MouseLocalPosition / TileSize;
	FTile TopLeftTile = FTile(FMath::TruncToInt(MousePosInTile.X - Dimension.X / 2), FMath::TruncToInt(MousePosInTile.Y - Dimension.Y / 2));

	DraggedItemTopLeftTile = FIntPoint(TopLeftTile.X, TopLeftTile.Y);

	return true;
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

		//GRÝD'ÝN BÜYÜKLÜÐÜ BELÝRLENÝR
		UCanvasPanelSlot* GridBorderSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
		GridBorderSlot->SetSize(FVector2D(InventorySubsystem->GetColumns() * TileSize, InventorySubsystem->GetRows() * TileSize));

		//GRID'ÝN KENARLARI ÇÝZÝLÝR
		CreateLineSegments();
		//GRID'ÝN ÝÇÝNÝ DOLDURMAK ÝÇÝN REFRESH FONKSÝYONU ÇAÐIRILIR
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

bool UInventoryGridWidget::IsRoomAvailableForPayload(AItemObject* _payload)
{
	if (_payload)
	{
		FTile _draggedItemTopLeftTile = FTile(DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y);
		int _index;
		bool _isRoomAvailable;

		InventorySubsystem->TileToIndex(_draggedItemTopLeftTile, _index);
		InventorySubsystem->IsRoomAvailable(_payload, _index, _isRoomAvailable);

		return _isRoomAvailable;

	}

	return false;
}

AItemObject* UInventoryGridWidget::GetPayload(UDragDropOperation* _dragDropOperation)
{
	//_dragdropOperation is valid
	if (_dragDropOperation && _dragDropOperation->Payload)
	{
		return Cast<AItemObject>(_dragDropOperation->Payload);
	}

	return nullptr;
}




void UInventoryGridWidget::Refresh()
{
	//GRID TEMÝZLENÝR
	GridCanvasPanel->ClearChildren();

	if (!InventorySubsystem)
	{
		InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	}

	//TÜM ÝTEMLAR ALINIR
	TMap<AItemObject*, FTile> _items;
	InventorySubsystem->GetAllItems(_items);

	//Her bir item'i ve tile'i bir for loop ile çizilir
	for (auto& Item : _items)
	{
		//Item ve tile alýnýr
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

void UInventoryGridWidget::OnGridBorderMouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	//GRID BORDER'A TIKLANDIÐINDA ÇALIÞACAK FONKSÝYON
	UE_LOG(LogTemp, Warning, TEXT("Grid Border Mouse Down"));
}

void UInventoryGridWidget::MousePositionInTile(FVector2D _mousePosition, bool& _right, bool& _down) const
{
	//MousePsition'un X değerini TileSize ile modunu alarak right ve down bool değerlerini döndürür
	_right = FMath::Fmod(_mousePosition.X, TileSize) > TileSize / 2;
	_down = FMath::Fmod(_mousePosition.Y, TileSize) > TileSize / 2;

}
