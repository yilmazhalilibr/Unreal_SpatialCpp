// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySubsystem.h"
#include "ItemObject.h"
#include "Item.h"
#include "InventoryStructures.h"




void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//Items array make Resize with Columns and Rows
	Items.SetNum(Columns * Rows);

}

void UInventorySubsystem::TryAddItem(AItemObject* _itemObject, bool& _success)
{

	if (_itemObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("Items Num: %d"), Items.Num());

		for (int i = 0; i < Items.Num(); i++)
		{
			if (Items[i] != nullptr)
			{
				bool _isRoomAvailableBool;
				IsRoomAvailable(_itemObject, i, _isRoomAvailableBool);

				if (_isRoomAvailableBool)
				{
					AddItemAt(_itemObject, i);

					_success = true;
					return;
				}
				else
				{
					_success = false;
				}

			}

		}


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemObject is null(InventorySubSystem::TryAddItem fail)"));
		_success = false;
	}

}

void UInventorySubsystem::IsRoomAvailable(AItemObject*& _itemObject, int& _topleftIndex, bool& _roomEmpty)
{

	//ForEachIndex
	FTile _tile;
	IndexToTile(_topleftIndex, _tile);
	FIntPoint _dimensions = _itemObject->GetDimensions();

	int _startIndexJ = _tile.X;
	int _lastIndexJ = _tile.X - (_dimensions.X - 1);

	for (int j = _startIndexJ; j < _lastIndexJ; j++)
	{
		int _startIndexK = _tile.Y;
		int _lastIndexK = _tile.Y + (_dimensions.Y - 1);

		for (int k = _startIndexK; k < _lastIndexK; k++)
		{
			FTile _currentTile;
			_currentTile.X = j;
			_currentTile.Y = k;

			//IS TILE VALID

			if (_currentTile.X >= 0 && _currentTile.Y >= 0 && _currentTile.X < GetColumns() && _currentTile.Y < GetRows())
			{
				bool _isValid;
				int _tileToIndex;

				TileToIndex(_currentTile, _tileToIndex);
				GetItemAtIndex(_tileToIndex, _itemObject, _isValid);

				if (!_isValid)
				{
					_roomEmpty = false;
				}
				else
				{
					if (_itemObject)
					{
						_roomEmpty = false;
						return;
					}
					else
					{
						_roomEmpty = true;
						return;
					}

				}

			}
			else
			{

				_roomEmpty = false;
				return;

			}


		}


	}
	//Here can will be a bug because if _isValid condition will be false then _roomEmpty will be false but here return to true
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
		_itemObject = Items[_index];
		_isValid = true;
		return;
	}
	else
	{
		_isValid = false;
		return;
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
	int _lastIndexJ = _tile.X - (_dimensions.X - 1);

	for (int j = _startIndexJ; j < _lastIndexJ; j++)
	{
		int _startIndexK = _tile.Y;
		int _lastIndexK = _tile.Y + (_dimensions.Y - 1);

		for (int k = _startIndexK; k < _lastIndexK; k++)
		{
			FTile _currentTile;
			_currentTile.X = j;
			_currentTile.Y = k;

			int _tileToIndex;
			TileToIndex(_currentTile, _tileToIndex);

			//Items set array elements 
			Items[_tileToIndex] = _itemObject;


		}

	}
	IsDirty = true;

}
