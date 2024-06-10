// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/InventorySubsystem.h"
#include "SpatialInventory/ItemObject.h"
#include "SpatialInventory/Item.h"

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//Envanterler ileride buradan otomatik eklenecek
	//Inventories.Add("PlayerInventory", FInventoryData());


	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(CustomTimerHandle, this, &UInventorySubsystem::CustomTick, CustomTickInterval, true, 2.0f);
	}


}

void UInventorySubsystem::Deinitialize()
{
	Super::Deinitialize();

}

void UInventorySubsystem::CustomTick()
{
	// Tick iþlemlerinizi burada gerçekleþtirin

	if (IsDirty)
	{
		IsDirty = false;
		OnInventoryChanged.Broadcast();

	}

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

bool UInventorySubsystem::RemoveItemFromInventory(FName InventoryID, UItemObject* ItemObj)
{
	if (auto _inv = Inventories.Find(InventoryID))
	{
		for (int i = 0; i < _inv->InventorySlots.Num(); i++)
		{
			if (_inv->InventorySlots[i].ItemData.Dimensions == ItemObj->GetItemData().Dimensions)
			{
				_inv->InventorySlots.RemoveAt(i);
				return true;
			}
		}

		return true;
	}


	return false;
}

bool UInventorySubsystem::AddItemToInventory(FName InventoryID, FInventoryData InventoryData, int32 Amount)
{


	return false;
}

bool UInventorySubsystem::TryAddItemToInventory(FName InventoryName, UItemObject* ItemObject, int32 Amount)
{
	if (Inventories.Contains(InventoryName))
	{
		int _tempIndex = 0;

		FInventoryData* _inventory = &Inventories[InventoryName];
		if (_inventory == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory is null"));
			return false;
		}
		for (FInventorySlot slot; _inventory;)
		{
			if (IsRoomAvailable(InventoryName, ItemObject, _tempIndex))
			{
				UE_LOG(LogTemp, Warning, TEXT("room available"));
				AddItemAt(InventoryName, ItemObject, _tempIndex);
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

bool UInventorySubsystem::IsRoomAvailable(FName InventoryName, UItemObject* ItemObject, int32 TopLeftIndex)
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
			if (i >= 0 && j >= 0 && i < ItemObject->GetItemData().Dimensions.X && j < ItemObject->GetItemData().Dimensions.Y)
			{
				auto itemData = GetItemAtIndex(TileToIndex(FTile(i, j), ItemObject), InventoryName);


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

	float result = Index % ItemObject->GetDimensions().X;
	float result2 = Index / ItemObject->GetDimensions().X;

	return FTile(result, result2);

}

int32 UInventorySubsystem::TileToIndex(FTile Tile, UItemObject* ItemObject)
{
	return Tile.X + (Tile.Y * ItemObject->GetDimensions().X);
}

FItemData UInventorySubsystem::GetItemAtIndex(int32 Index, FName InventoryKey)
{
	if (Inventories.Contains(InventoryKey))
	{
		FInventoryData* inventory = &Inventories[InventoryKey];
		if (inventory == nullptr || inventory->InventorySlots.IsValidIndex(Index))
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory is null"));
			return FItemData();
		}


		//return inventory->InventorySlots[Index].ItemData; bu kodda ItemData için null kontrolü yapýlmalý
		if (!inventory->InventorySlots.IsEmpty())
		{
			return inventory->InventorySlots[Index].ItemData;
		}
		else
		{
			return FItemData();
		}



	}
	else
	{
		return FItemData();
	}

}

void UInventorySubsystem::AddItemAt(FName InventoryName, UItemObject* ItemObject, int32 TopLeftIndex)
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
			/*if (Inventories.Contains(ItemObject->GetInventoryData().InventoryKey))
			{*/

			auto _inven = Inventories.Find(InventoryName);
			_inven->InventorySlots.Add(FInventorySlot(ItemObject->GetItemData(), 1));


			//}

		}

	}
	IsDirty = true;


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
