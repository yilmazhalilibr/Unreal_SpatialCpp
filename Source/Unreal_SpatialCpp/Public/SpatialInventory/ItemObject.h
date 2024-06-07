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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Data")
	FItemData ItemData;

public:
	//Constructor
	UItemObject();

	UFUNCTION(BlueprintCallable, Category = "Item Data")
	FIntPoint GetDimensions() { return ItemData.Dimensions; }

	UFUNCTION(BlueprintCallable, Category = "Item Data")
	FItemData GetItemData() { return ItemData; }


};
