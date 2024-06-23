// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataStructures.generated.h"



//SItemData adýnda bir struct oluþturuyoruz. Bu struct, itemlerin isimlerini ve sayýlarýný tutacak.
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString ItemUniqueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	bool Stackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FVector2D IconCordinateinInventory;
};

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	int32 Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	FVector2D IconCordinateinInventory;
};


USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_USTRUCT_BODY()

	FVector2D Start;
	FVector2D End;
};



UCLASS(Blueprintable)
class UNREAL_SPATIALCPP_API UDataStructures : public UObject
{
	GENERATED_BODY()

};
