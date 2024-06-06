// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventorySubsystem.h"
#include "Item.h"

#include "ItemObject.generated.h"


UCLASS(Blueprintable, BlueprintType)
class UNREAL_SPATIALCPP_API UItemObject : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FInventoryData InventoryData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Data")
	FIntPoint Dimensions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Data")
	UMaterialInterface* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Data")
	UMaterialInterface* IconRotated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Data")
	TSubclassOf<AItem> ItemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Data")
	bool Rotated;

public:
	//Constructor
	UItemObject();

	UFUNCTION(BlueprintCallable, Category = "Item Data")
	FInventoryData GetInventoryData() { return InventoryData; }

	UFUNCTION(BlueprintCallable, Category = "Item Data")
	FIntPoint GetDimensions() { return Dimensions; }

};
