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

	// InventorySubsystem'u kontrol edin
	//// Widget referanslar�n�n do�ru �ekilde ba�land���n� kontrol edin
	//if (!CanvasPanel)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("CanvasPanel is not bound."));
	//	CanvasPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("CanvasPanel"));
	//	WidgetTree->RootWidget = CanvasPanel;
	//}

	//if (!BackgroundBorder)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("BackgroundBorder is not bound."));
	//	BackgroundBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("BackgroundBorder"));
	//	CanvasPanel->AddChildToCanvas(BackgroundBorder); // AddChild yerine AddChildToCanvas kullan�l�yor
	//}

	//if (!InventoryGrid)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("InventoryGrid is not bound."));
	//	InventoryGrid = WidgetTree->ConstructWidget<UInventoryGridWidget>(UInventoryGridWidget::StaticClass(), TEXT("InventoryGrid"));
	//	BackgroundBorder->AddChild(InventoryGrid);
	//}

	//if (!BackgroundBlur)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("BackgroundBlur is not bound."));
	//	BackgroundBlur = WidgetTree->ConstructWidget<UBackgroundBlur>(UBackgroundBlur::StaticClass(), TEXT("BackgroundBlur"));
	//	CanvasPanel->AddChildToCanvas(BackgroundBlur); // AddChild yerine AddChildToCanvas kullan�l�yor
	//}

	//// Log success if all widgets are bound
	//if (CanvasPanel && BackgroundBorder && InventoryGrid && BackgroundBlur)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("All widgets successfully bound."));
	//}


}

void UInventoryWidget::NativeConstruct()
{

	InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();

	if (InventoryGrid)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryGrid found."));
		InventoryGrid->InitializeGrids();

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryGrid is not bound."));
	}


}
