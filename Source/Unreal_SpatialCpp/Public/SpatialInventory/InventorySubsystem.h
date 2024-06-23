// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataStructures.h"
#include "InventorySubsystem.generated.h"

/**
 *
 */


UCLASS()
class UNREAL_SPATIALCPP_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToInventory(FString _inventoryName, FInventoryData _itemData, bool& _success);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInventoryData GetInventory(FString _inventoryName, bool& _success);

protected:
	TMap<FString, FInventoryData> Inventories;


};
