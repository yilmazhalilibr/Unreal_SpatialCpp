#include "InventoryWidget.h"
#include "InventorySubsystem.h"
#include "InventoryGridWidget.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetTree.h" // UWidgetTree için gerekli baþlýk dosyasý
#include "Components/Border.h"
#include "Components/BackgroundBlur.h"
#include "Components/CanvasPanelSlot.h"
#include "Input/Events.h"
#include "Input/Reply.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/DragDropOperation.h"




void UInventoryWidget::NativeConstruct()
{

	InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();

	if (InventoryGrid)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryGrid found."));
		InventoryGrid->InitializeGrids(this);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryGrid is not bound."));
	}

	//BackgorundBorder'i valid et ve sonra mouse button down eventini baðla
	if (BackgroundBorder)
	{
		BackgroundBorder->OnMouseButtonDownEvent.BindUFunction(this, FName("OnBackgroundBorderMouseDown"));

	}


}



FReply UInventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDown"));

	if (BackgroundBorder && InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDown LeftMouseButton"));
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{


	return false;
}
