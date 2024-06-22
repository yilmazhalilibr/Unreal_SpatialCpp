// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySubsystem.h"
#include "ItemObject.h"
#include "Item.h"
#include "InventoryStructures.h"

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//Items array make Resize with Columns and Rows
	Items.SetNum(Columns * Rows);

	//Timer for testing and use lambda function
	GetWorld()->GetTimerManager().SetTimer(TimerHandleTick, [this]()
		{
			CustomTick(0.05);
		}, 0.05f, true);
}

void UInventorySubsystem::Deinitialize()
{
	//Clear Timer
	GetWorld()->GetTimerManager().ClearTimer(TimerHandleTick);
}

void UInventorySubsystem::CustomTick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("CustomTick"));
	if (IsDirty)
	{
		IsDirty = false;
		OnInventoryChanged.Broadcast();
	}
}

void UInventorySubsystem::TryAddItem(AItemObject* _itemObject, bool& _success)
{
	if (_itemObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("Items Num: %d"), Items.Num());

		for (int i = 0; i < Items.Num(); i++)
		{
			if (Items[i] == nullptr)
			{
				bool _isRoomAvailableBool;
				IsRoomAvailable(_itemObject, i, _isRoomAvailableBool);

				if (_isRoomAvailableBool)
				{
					AddItemAt(_itemObject, i);
					_success = true;
					return;
				}
			}
		}
		_success = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemObject is null (InventorySubSystem::TryAddItem fail)"));
		_success = false;
	}
}

void UInventorySubsystem::GetAllItems(TMap<AItemObject*, FTile>& _allItems)
{
	_allItems.Empty();
	AItemObject* _currentItemObject;
	FTile _currentTile;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i] != nullptr)
		{
			if (!_allItems.Contains(Items[i]))
			{
				_currentItemObject = Items[i];
				IndexToTile(i, _currentTile);
				_allItems.Add(_currentItemObject, _currentTile);
			}
		}
	}
}

void UInventorySubsystem::RemoveItem(AItemObject* _itemObject)
{
	//Items.Remove(_itemObject);
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i] == _itemObject)
		{
			Items[i] = nullptr;
			IsDirty = true;
		}
	}
}

void UInventorySubsystem::SpawnItemFromActor(AItemObject* _itemObject, AActor* _actor, bool _groundClamp)
{
	if (!_itemObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemObject is null (InventorySubsystem::SpawnItemFromActor)"));
		return;
	}

	auto _location = (_actor->GetActorForwardVector() * 150) + _actor->GetActorLocation();

	if (_groundClamp)
	{
		FHitResult _hitResult;
		FVector _start = _location;
		FVector _end = _location - FVector(0, 0, 1000);

		FCollisionQueryParams _collisionQueryParams;
		//_collisionQueryParams.AddIgnoredActor(nullptr);

		if (GetWorld()->LineTraceSingleByChannel(_hitResult, _start, _end, ECollisionChannel::ECC_Visibility, _collisionQueryParams))
		{
			_location = _hitResult.Location;
		}
		else
		{
			_location = _location - FVector(0, 0, 1000);
		}
	}

	//ItemObject'i _location'a spawn et
	FActorSpawnParameters _spawnParameters;
	_spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AItem* _spawnedItem = GetWorld()->SpawnActor<AItem>(_itemObject->GetItemClass(), _location, FRotator::ZeroRotator, _spawnParameters);

	FIntPoint _dimensions;
	UMaterialInterface* _icon;
	UMaterialInterface* _iconRotated;
	TSubclassOf<AItem> _itemClass;
	bool _rotated;

	_itemObject->GetAllSettings(_dimensions, _icon, _iconRotated, _itemClass, _rotated);
}

void UInventorySubsystem::IsRoomAvailable(const AItemObject* _itemObject, int& _topleftIndex, bool& _roomEmpty)
{
	FTile _tile;
	IndexToTile(_topleftIndex, _tile);
	FIntPoint _dimensions = _itemObject->Dimensions;

	int _startIndexJ = _tile.X;
	int _lastIndexJ = _tile.X + (_dimensions.X - 1);

	for (int j = _startIndexJ; j <= _lastIndexJ; j++)
	{
		int _startIndexK = _tile.Y;
		int _lastIndexK = _tile.Y + (_dimensions.Y - 1);

		for (int k = _startIndexK; k <= _lastIndexK; k++)
		{
			FTile _currentTile;
			_currentTile.X = j;
			_currentTile.Y = k;

			// IS TILE VALID
			if (_currentTile.X >= 0 && _currentTile.Y >= 0 && _currentTile.X < GetColumns() && _currentTile.Y < GetRows())
			{
				bool _isValid = false;
				int _tileToIndex = -1;

				TileToIndex(_currentTile, _tileToIndex);
				AItemObject* _tempItemObject = nullptr;
				GetItemAtIndex(_tileToIndex, _tempItemObject, _isValid);

				if (!_isValid || _tempItemObject)
				{
					_roomEmpty = false;
					return;
				}
			}
			else
			{
				_roomEmpty = false;
				return;
			}
		}
	}

	// If we exit the loops without finding an invalid tile or an occupied one, the room is empty
	_roomEmpty = true;
}

void UInventorySubsystem::IndexToTile(int& _index, FTile& _tile)
{
	_tile.X = _index % Columns;
	_tile.Y = _index / Columns;
}

void UInventorySubsystem::GetItemAtIndex(int _index, AItemObject*& _itemObject, bool& _isValid)
{
	if (Items.IsValidIndex(_index))
	{
		_itemObject = Items[_index]; // Bu satırdaki hata düzeltildi
		_isValid = true;
	}
	else
	{
		_isValid = false;
	}
}

void UInventorySubsystem::TileToIndex(FTile& _tile, int& _index)
{
	_index = _tile.X + (_tile.Y * Columns);
}

void UInventorySubsystem::AddItemAt(AItemObject*& _itemObject, int& _topleftIndex)
{
	FTile _tile;
	IndexToTile(_topleftIndex, _tile);
	FIntPoint _dimensions = _itemObject->GetDimensions();

	int _startIndexJ = _tile.X;
	int _lastIndexJ = _tile.X + (_dimensions.X - 1);

	for (int j = _startIndexJ; j <= _lastIndexJ; j++)
	{
		int _startIndexK = _tile.Y;
		int _lastIndexK = _tile.Y + (_dimensions.Y - 1);

		for (int k = _startIndexK; k <= _lastIndexK; k++)
		{
			FTile _currentTile;
			_currentTile.X = j;
			_currentTile.Y = k;

			int _tileToIndex;
			TileToIndex(_currentTile, _tileToIndex);

			// Items set array elements 
			if (Items.IsValidIndex(_tileToIndex))
			{
				Items[_tileToIndex] = _itemObject;
			}
		}
	}
	IsDirty = true;
}
