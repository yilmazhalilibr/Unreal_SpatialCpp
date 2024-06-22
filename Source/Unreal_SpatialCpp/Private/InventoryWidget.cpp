#include "InventoryWidget.h"
#include "InventorySubsystem.h"
#include "InventoryGridWidget.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetTree.h" // UWidgetTree için gerekli başlık dosyası
#include "Components/Border.h"
#include "Components/BackgroundBlur.h"
#include "Components/CanvasPanelSlot.h"
#include "Input/Events.h"
#include "Input/Reply.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemObject.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();

	if (InventorySubsystem)
	{
		if (InventoryGrid)
		{
			UE_LOG(LogTemp, Warning, TEXT("InventoryGrid found."));
			InventoryGrid->InitializeGrids(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("InventoryGrid is not bound."));
		}

		// BackgroundBorder'ı valid et ve sonra mouse button down eventini bağla
		if (BackgroundBorder)
		{
			BackgroundBorder->OnMouseButtonDownEvent.BindUFunction(this, FName("OnBackgroundBorderMouseDown"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BackgroundBorder is not bound."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem is not found."));
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
	AItemObject* ItemObject = Cast<AItemObject>(InOperation->Payload);

	// Payload'ı AItemObject'e cast et
	if (ItemObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("NativeOnDrop - TRUE"));

		APlayerController* PlayerController = GetOwningPlayer();
		if (PlayerController)
		{
			AActor* _player = PlayerController->GetPawn();
			if (_player && InventorySubsystem)
			{
				InventorySubsystem->SpawnItemFromActor(ItemObject, _player, true);
				InventorySubsystem->RemoveItem(ItemObject);
				return true;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Player or InventorySubsystem is null."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerController is null."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ItemObject is null."));
	}

	UE_LOG(LogTemp, Warning, TEXT("NativeOnDrop - FALSE"));
	return false;
}
