#include "InventoryWidget.h"
#include "InventorySubsystem.h"
#include "InventoryGridWidget.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// InventorySubsystem'u kontrol edin
	InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();

	// BorderGrid ve InventoryGridWidget'ýn doðru þekilde baðlandýðýný kontrol edin
	if (GetGrid() && InventorySubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryGridWidget successfully bound."));
		GetGrid()->InitializeGrids(InventorySubsystem, TileSize);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to bind InventoryGridWidget."));
		////Eðer yoksa Grid'i oluþtur
		//UInventoryGridWidget* Grid = CreateWidget<UInventoryGridWidget>(GetWorld(), UInventoryGridWidget::StaticClass());
		//Grid->InitializeGrids(InventorySubsystem, TileSize);
		//InventoryGrid = Grid;

	}


}
