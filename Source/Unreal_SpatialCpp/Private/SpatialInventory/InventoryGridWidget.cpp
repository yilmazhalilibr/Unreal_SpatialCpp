#include "SpatialInventory/InventoryGridWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/Engine.h" // GEngine için gerekli
#include "Components/BorderSlot.h" 
#include <Blueprint/SlateBlueprintLibrary.h>

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("UInventoryGridWidget::NativeConstruct"));

	// Initialize the inventory grid widget
	InitializeInventoryGridWidget();

}

void UInventoryGridWidget::OnPaint(FPaintContext& Context) const
{
	Super::OnPaint(Context);

	for (const FSLine& Line : Lines)
	{
		FGeometry Geometry = GridBorder->GetCachedGeometry();
		FVector2D LocalTopLeft = USlateBlueprintLibrary::GetLocalTopLeft(Geometry);

		FVector2D Start = LocalTopLeft + Line.X;
		FVector2D End = LocalTopLeft + Line.Y;

		//WidgetBlueprintLibraryInstance->DrawLine(Context, Start, End, FLinearColor::White, false);

		  // Çizgi çizme iþlemi
		//LineColor RGB deðeri 0.5 , A deðeri 1.0
		FLinearColor LineColor = FLinearColor(0.5f, 0.5f, 0.5f, 0.5f);
		TArray<FVector2D> Points;
		Points.Add(Start);
		Points.Add(End);

		FSlateDrawElement::MakeLines(
			Context.OutDrawElements,
			Context.LayerId,
			Context.AllottedGeometry.ToPaintGeometry(),
			Points,
			ESlateDrawEffect::None,
			LineColor,
			true,
			1.0f
		);


	}

	//LATER WE WILL ADD DRAW DROP LOCATION

	return;
}

void UInventoryGridWidget::InitializeInventoryGridWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("UInventoryGridWidget::InitializeInventoryGridWidget"));
	WidgetBlueprintLibraryInstance = NewObject<UWidgetBlueprintLibrary>();

	if (WidgetTree)
	{
		UE_LOG(LogTemp, Warning, TEXT("WidgetTree is valid"));
		// Create and configure the CanvasPanel
		CanvasPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("CanvasPanel"));
		WidgetTree->RootWidget = CanvasPanel;

		// Set up GridBorder
		GridBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("GridBorder"));
		GridBorder->SetBrushColor(FLinearColor(1.0f, 0.0f, 0.0f, 0.25f));  // Renk kýrmýzý olarak ayarlandý
		UCanvasPanelSlot* BorderSlot = Cast<UCanvasPanelSlot>(CanvasPanel->AddChildToCanvas(GridBorder));
		BorderSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
		BorderSlot->SetPosition(FVector2D(0.0f, 0.0f));
		BorderSlot->SetSize(FVector2D(150.0f, 600.0f));
		BorderSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		GridBorder->SetPadding(FMargin(0.0f));

		// Set up GridCanvasPanel
		GridCanvasPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("GridCanvasPanel"));
		GridBorder->SetContent(GridCanvasPanel);

		UBorderSlot* GridCanvasSlot = Cast<UBorderSlot>(GridCanvasPanel->Slot);
		if (GridCanvasSlot)
		{
			UE_LOG(LogTemp, Warning, TEXT("GridCanvasSlot is valid"));

			GridCanvasSlot->SetHorizontalAlignment(HAlign_Fill);
			GridCanvasSlot->SetVerticalAlignment(VAlign_Fill);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to cast BorderSlot for GridCanvasPanel"));
		}
	}

}


void UInventoryGridWidget::InitializeGrid(UInventorySubsystem inventorySubSystem, float tileSize)
{
	//Gridborder'n Size'ini ayarla
	UCanvasPanelSlot* BorderSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
	if (BorderSlot)
	{
		BorderSlot->SetSize(FVector2D(inventorySubSystem.GetColumns() * tileSize, inventorySubSystem.GetRows() * tileSize));
		CreateLineSegments();
		UE_LOG(LogTemp, Warning, TEXT("GridBorder's size is set , Created line segments"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast CanvasPanelSlot for GridBorder"));
	}

}

void UInventoryGridWidget::CreateLineSegments()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < InventorySubsystem->GetColumns(); i++)
	{
		x = i * TileSize;

		auto xResult = FVector2D(x, x);
		auto yResult = FVector2D(0, InventorySubsystem->GetRows() * TileSize);
		auto line = FSLine(xResult, yResult);
		Lines.Add(FSLine(line));

	}
	for (int i = 0; i < InventorySubsystem->GetRows(); i++)
	{
		y = i * TileSize;

		auto xResult = FVector2D(0, InventorySubsystem->GetColumns() * TileSize);
		auto yResult = FVector2D(y, y);
		auto line = FSLine(xResult, yResult);
		Lines.Add(FSLine(line));

	}


}