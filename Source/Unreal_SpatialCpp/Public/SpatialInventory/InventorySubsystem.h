// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "InventorySubsystem.generated.h"

class ItemObject;


//Tile Structure
USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Y;
};

USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StatID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StatValue;
};


USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemMainType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemSubType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStat> StatsArray;
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;
};

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName InventoryKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventorySlot> InventorySlots;
};




UCLASS()
class UNREAL_SPATIALCPP_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY()
	TMap<FName, FInventoryData> Inventories;

	UPROPERTY()
	bool IsDirty;

public:

	//Get Inventory Data
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TMap<FName, FInventoryData> GetInventories();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddInventory(FName InventoryID, FInventoryData InventoryData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveInventory(FName InventoryID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItemToInventory(FName InventoryID, FInventoryData InventoryData, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryAddItemToInventory(FName InventoryID, UItemObject* ItemObject, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsRoomAvailable(UItemObject* ItemObject, int32 TopLeftIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FTile IndexToTile(int32 Index, UItemObject* ItemObject);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 TileToIndex(FTile Tile, UItemObject* ItemObject);

	/*UFUNCTION(BlueprintCallable, Category = "Inventory")
	FTile ForEachIndex(UItemObject* ItemObject, int32 TopLeftIndex);*/

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FItemData GetItemAtIndex(int32 Index, FName InventoryKey);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemAt(UItemObject* ItemObject, int32 TopLeftIndex);

};
