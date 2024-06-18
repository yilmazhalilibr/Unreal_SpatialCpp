#include "InventoryWidget.h"
#include "InventorySubsystem.h"
#include "InventoryGridWidget.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetTree.h" // UWidgetTree i�in gerekli ba�l�k dosyas�
#include "Components/Border.h"
#include "Components/BackgroundBlur.h"





void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

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


}
