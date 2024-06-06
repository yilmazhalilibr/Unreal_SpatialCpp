// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/InventorySubsystem.h"

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UInventorySubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TMap<FName, FInventoryData> UInventorySubsystem::GetInventories()
{
	if (Inventories.IsEmpty())
	{
		return TMap<FName, FInventoryData>();

	}

	return Inventories;
}

bool UInventorySubsystem::AddInventory(FName InventoryID, FInventoryData InventoryData)
{
	if (Inventories.Contains(InventoryID))
	{
		return false;
	}

	Inventories.Add(InventoryID, InventoryData);
	return true;
}



