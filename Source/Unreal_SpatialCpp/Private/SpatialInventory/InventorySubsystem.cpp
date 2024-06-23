// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/InventorySubsystem.h"

void UInventorySubsystem::AddItemToInventory(FString _inventoryName, FInventoryData _itemData, bool& _success)
{
   
}


FInventoryData UInventorySubsystem::GetInventory(FString _inventoryName, bool& _success)
{
	if (Inventories.Contains(_inventoryName))
	{

		FInventoryData* _invt = Inventories.Find(_inventoryName);
		_success = true;

		return *_invt;
	}
	else
	{
		_success = false;
		return FInventoryData();
	}

}
