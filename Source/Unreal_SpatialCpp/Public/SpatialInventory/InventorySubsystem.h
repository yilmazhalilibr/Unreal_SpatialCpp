// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
//add timer handle
#include "TimerManager.h"
#include "InventorySubsystem.generated.h"

//On event dispatcher for inventory
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

class ItemObject;
class AItem;

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
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStat> StatsArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Rotated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* IconRotated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Dimensions;
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
	int32 InventoryRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InventoryColumn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InventoryGridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventorySlot> InventorySlots;
};




UCLASS()
class UNREAL_SPATIALCPP_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	// Tick fonksiyonunu tanýmlayýn
	void CustomTick();
	// Tick fonksiyonunu düzenli olarak çaðýrmak için bir zamanlayýcý
	FTimerHandle CustomTimerHandle;
	// Tick zaman aralýðý
	float CustomTickInterval = 0.1f;  // Her 0.1 saniyede bir tick


protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY()
	TMap<FName, FInventoryData> Inventories;

	UPROPERTY()
	bool IsDirty;

public:

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

	//Get Inventory Data
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TMap<FName, FInventoryData> GetInventories();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddInventory(FName InventoryID, FInventoryData InventoryData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveInventory(FName InventoryID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemFromInventory(FName InventoryID, UItemObject* ItemObj);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItemToInventory(FName InventoryID, FInventoryData InventoryData, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryAddItemToInventory(FName InventoryName, UItemObject* ItemObject, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsRoomAvailable(FName InventoryName, UItemObject* ItemObject, int32 TopLeftIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FTile IndexToTile(int32 Index, UItemObject* ItemObject);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 TileToIndex(FTile Tile, UItemObject* ItemObject);

	/*UFUNCTION(BlueprintCallable, Category = "Inventory")
	FTile ForEachIndex(UItemObject* ItemObject, int32 TopLeftIndex);*/

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FItemData GetItemAtIndex(int32 Index, FName InventoryKey);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemAt(FName InventoryName, UItemObject* ItemObject, int32 TopLeftIndex);

};
