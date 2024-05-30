#include "SpatialInventory/InventoryWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/BackgroundBlur.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include "SpatialInventory/InventoryGridWidget.h"
#include "Engine/Engine.h" // GEngine için gerekli


void UInventoryWidget::NativePreConstruct()
{
	UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget::PreNativeConstruct"));

	// Initialize the inventory widget
	InitializeInventoryWidget();
}



void UInventoryWidget::InitializeInventoryWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget::InitializeInventoryWidget"));

	//if runtime check is needed



	if (WidgetTree)
	{
		// Create and configure the CanvasPanel
		CanvasPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("CanvasPanel"));
		WidgetTree->RootWidget = CanvasPanel;

		// Set up BackgroundBorder
		BackgroundBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("BackgroundBorder"));
		BackgroundBorder->SetBrushColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.2f));
		UCanvasPanelSlot* BorderSlot = Cast<UCanvasPanelSlot>(CanvasPanel->AddChildToCanvas(BackgroundBorder));
		BorderSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		BorderSlot->SetOffsets(FMargin(0.0f, 0.0f, 0.0f, 0.0f));

		// Set up BackgroundBlur
		BackgroundBlur = WidgetTree->ConstructWidget<UBackgroundBlur>(UBackgroundBlur::StaticClass(), TEXT("BackgroundBlur"));
		BackgroundBlur->SetBlurStrength(2.0f);
		BackgroundBorder->AddChild(BackgroundBlur);

		// Set up InventoryGridWidget
		GridWidget = WidgetTree->ConstructWidget<UInventoryGridWidget>(UInventoryGridWidget::StaticClass(), TEXT("InventoryGridWidget"));
		if (GridWidget)
		{
			UCanvasPanelSlot* GridSlot = Cast<UCanvasPanelSlot>(CanvasPanel->AddChildToCanvas(GridWidget));
			if (GridSlot)
			{

				UE_LOG(LogTemp, Warning, TEXT("InventoryGridWidget created successfully"));
				GridSlot->SetAnchors(FAnchors(1.0f, 0.5f, 1.0f, 0.5f));
				GridSlot->SetPosition(FVector2D(-50.0f, 0.0f));
				GridSlot->SetSize(FVector2D(100.0f, 500.0f));
				GridSlot->SetAlignment(FVector2D(1.0f, 0.5f));
				//GridSlot->bAutoSize = true;  // Size to Content = true

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to cast CanvasPanelSlot for InventoryGridWidget"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to create InventoryGridWidget"));
		}
	}
}
