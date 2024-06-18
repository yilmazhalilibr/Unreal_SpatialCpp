#include "InventoryWidget.h"
#include "InventorySubsystem.h"
#include "InventoryGridWidget.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetTree.h" // UWidgetTree için gerekli baþlýk dosyasý
#include "Components/Border.h"
#include "Components/BackgroundBlur.h"
#include "Components/CanvasPanelSlot.h"
#include "Input/Events.h"
#include "Blueprint/WidgetBlueprintLibrary.h"



void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();
}


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

	////BackgorundBorder'i valid et ve sonra mouse button down eventini baðla
	//if (BackgroundBorder)
	//{
	//	BackgroundBorder->OnMouseButtonDownEvent.BindUFunction(this, FName("OnBackgroundBorderMouseDown"));

	//}


}

//
//FReply UInventoryWidget::OnBackgroundBorderMouseDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
//{
//	UE_LOG(LogTemp, Warning, TEXT("BackgroundBorder Mouse Down"));
//
//	return FReply::Handled();
//}
//
//FReply UInventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//
//	if (BackgroundBorder && InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
//	{
//		OnBackgroundBorderMouseDown(InGeometry, InMouseEvent);
//		return FReply::Handled();
//	}
//
//	return FReply::Unhandled();
//}
