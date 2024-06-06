// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/InventorySubsystem.h"
#include "SpatialInventory/ItemObject.h"

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FInventoryData _inventoryData{ "PlayerInventory",5,10,50 };

	AddInventory(_inventoryData.InventoryKey, _inventoryData);

	int _invenSize = _inventoryData.Column * _inventoryData.Row;

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

bool UInventorySubsystem::RemoveInventory(FName InventoryID)
{
	if (Inventories.Contains(InventoryID))
	{
		Inventories.Remove(InventoryID);
		return true;
	}
	return false;
}

bool UInventorySubsystem::AddItemToInventory(FName InventoryID, FInventoryData InventoryData, int32 Amount)
{


	return false;
}

bool UInventorySubsystem::TryAddItemToInventory(FName InventoryID, UItemObject* ItemObject, int32 Amount)
{
	if (Inventories.Contains(InventoryID))
	{
		int _tempIndex = 0;

		FInventoryData* _inventory = &Inventories[InventoryID];
		if (_inventory == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory is null"));
			return false;
		}
		for (FInventorySlot slot; _inventory;)
		{
			if (IsRoomAvailable(ItemObject, _tempIndex))
			{
				UE_LOG(LogTemp, Warning, TEXT("room available"));
				AddItemAt(ItemObject, _tempIndex);
				return true;

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("room not available"));
			}
			_tempIndex++;

		}

		return false;
	}
	return false;
}

bool UInventorySubsystem::IsRoomAvailable(UItemObject* ItemObject, int32 TopLeftIndex)
{

	auto tile = IndexToTile(TopLeftIndex, ItemObject);
	auto dimension = ItemObject->GetDimensions();
	int32 last = ((dimension.X - 1) + tile.X);

	for (int32 i = tile.X; i < last; i++)
	{
		int32 last2 = ((dimension.Y - 1) + tile.Y);
		for (int32 j = tile.Y; j < last2; j++)
		{
			//Ileride burda deðiþiklik yapýlacak HATALI IF BLOGU YAPTI
			if (i >= 0 && j >= 0 && i < 0 && j < 0)
			{
				auto itemData = GetItemAtIndex(TileToIndex(FTile(i, j), ItemObject), ItemObject->GetInventoryData().InventoryKey);


			}
			else
			{
				return false;
			}

		}
	}




	return true;
}



FTile UInventorySubsystem::IndexToTile(int32 Index, UItemObject* ItemObject)
{

	float result = Index % ItemObject->GetInventoryData().Column;
	float result2 = Index / ItemObject->GetInventoryData().Column;

	return FTile(result, result2);

}

int32 UInventorySubsystem::TileToIndex(FTile Tile, UItemObject* ItemObject)
{
	return Tile.X + (Tile.Y * ItemObject->GetInventoryData().Column);
}

//FTile UInventorySubsystem::ForEachIndex(UItemObject* ItemObject, int32 TopLeftIndex)
//{
//	auto tile = IndexToTile(TopLeftIndex, ItemObject);
//	auto dimension = ItemObject->GetDimensions();
//	int32 last = ((dimension.X - 1) + tile.X);
//
//	for (int32 i = tile.X; i < last; i++)
//	{
//		int32 last2 = ((dimension.Y - 1) + tile.Y);
//		for (int32 j = tile.Y; j < last2; j++)
//		{
//
//		}
//	}
//
//
//	//IS TILE VALID FUNCTION
//
//	if (tile.X >= 0 && tile.Y >= 0 && tile.X < 0 && tile.Y < 0)
//	{
//
//	}
//
//
//
//}

FItemData UInventorySubsystem::GetItemAtIndex(int32 Index, FName InventoryKey)
{
	if (Inventories.Contains(InventoryKey))
	{
		FInventoryData* inventory = &Inventories[InventoryKey];
		if (inventory == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory is null"));
			return FItemData();
		}

		return inventory->InventorySlots[Index].ItemData;

	}
	else
	{
		return FItemData();
	}

}

void UInventorySubsystem::AddItemAt(UItemObject* ItemObject, int32 TopLeftIndex)
{

	auto tile = IndexToTile(TopLeftIndex, ItemObject);
	auto dimension = ItemObject->GetDimensions();
	int32 last = ((dimension.X - 1) + tile.X);

	for (int32 i = tile.X; i < last; i++)
	{
		int32 last2 = ((dimension.Y - 1) + tile.Y);
		for (int32 j = tile.Y; j < last2; j++)
		{
			//			TileToIndex(FTile(i, j), ItemObject);
			if (Inventories.Contains(ItemObject->GetInventoryData().InventoryKey))
			{
				auto _inven = Inventories.Find(ItemObject->GetInventoryData().InventoryKey);

				_inven->InventorySlots.Add(FInventorySlot(ItemObject->GetInventoryData().InventorySlots[0].ItemData, 1));


			}

		}

	}
	IsDirty = true;


}







