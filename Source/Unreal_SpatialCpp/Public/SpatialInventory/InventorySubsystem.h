// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventorySubsystem.generated.h"


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

	TMap<FName, FInventoryData> Inventories;

public:
	//Get Inventory Data
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TMap<FName, FInventoryData> GetInventories();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddInventory(FName InventoryID, FInventoryData InventoryData);

};
