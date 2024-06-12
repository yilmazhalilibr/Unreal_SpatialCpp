#include "InventoryWidget.h"
#include "InventorySubsystem.h"
#include "InventoryGridWidget.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// InventorySubsystem'u kontrol edin
	InventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	if (!InventorySubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("InventorySubsystem not found."));
	}
	// BorderGrid ve InventoryGridWidget'ýn doðru þekilde baðlandýðýný kontrol edin
	if (GetGrid() && InventorySubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryGridWidget successfully bound."));
		GetGrid()->InitializeGrids();
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
