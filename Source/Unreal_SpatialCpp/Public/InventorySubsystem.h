// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventorySubsystem.generated.h"

/**
 *
 */

class AItemObject;
class AInventoryStructures;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);



UCLASS()
class UNREAL_SPATIALCPP_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	//Initialize method
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//Destructor
	virtual void Deinitialize() override;

	UFUNCTION()
	void CustomTick(float DeltaTime);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

	UFUNCTION()
	void OnInventoryChangedBroadcast() { OnInventoryChanged.Broadcast(); }

	UFUNCTION(BlueprintCallable)
	void SetupInventory(int _columns, int _rows, float _tileSize, FLinearColor _lineColor, float _lineThickness)
	{
		Columns = _columns;
		Rows = _rows;
		TileSize = _tileSize;
		LineColor = _lineColor;
		LineThickness = _lineThickness;
	}


	UFUNCTION(BlueprintCallable)
	int GetColumns() { return Columns; }

	UFUNCTION(BlueprintCallable)
	int GetRows() { return Rows; }

	UFUNCTION(BlueprintCallable)
	void SetColumns(int _columns) { Columns = _columns; }

	UFUNCTION(BlueprintCallable)
	void SetRows(int _rows) { Rows = _rows; }

	UFUNCTION(BlueprintCallable)
	void SetTileSize(float _tileSize) { TileSize = _tileSize; }

	UFUNCTION(BlueprintCallable)
	void SetLineColor(FLinearColor _lineColor) { LineColor = _lineColor; }

	UFUNCTION(BlueprintCallable)
	void SetLineThickness(float _lineThickness) { LineThickness = _lineThickness; }

	UFUNCTION(BlueprintCallable)
	float GetTileSize() { return TileSize; }

	UFUNCTION(BlueprintCallable)
	FLinearColor GetLineColor() { return LineColor; }

	UFUNCTION(BlueprintCallable)
	float GetLineThickness() { return LineThickness; }

	UFUNCTION(BlueprintCallable)
	void TryAddItem(AItemObject* _itemObject, bool& _success);

	UFUNCTION(BlueprintCallable)
	TArray<AItemObject*> GetItems() { return Items; }

	UFUNCTION(BlueprintCallable)
	void GetAllItems(TMap<AItemObject*, FTile>& _allItems);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(AItemObject* _itemObject);

	UPROPERTY()
	FTimerHandle TimerHandleTick;

	UFUNCTION(BlueprintCallable)
	void SpawnItemFromActor(AItemObject* _itemObject, AActor* _actor, bool _groundClamp);

	//Function IsRoomAvailable
	UFUNCTION(BlueprintCallable)
	void IsRoomAvailable(const AItemObject* _itemObject, int& _topleftIndex, bool& _roomEmpty);

	UFUNCTION(BlueprintCallable)
	void IndexToTile(int& _index, FTile& _tile);

	UFUNCTION(BlueprintCallable)
	void GetItemAtIndex(int _index, AItemObject*& _itemObject, bool& _isValid);

	UFUNCTION(BlueprintCallable)
	void TileToIndex(FTile& _tile, int& _index);

	UFUNCTION(BlueprintCallable)
	void AddItemAt(AItemObject*& _itemObject, int& _topleftIndex);


	UPROPERTY()
	bool DoOnceTryAddItem = false;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	FLinearColor LineColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	float LineThickness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool IsDirty;

	//Items list 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<AItemObject*> Items;

	


};
