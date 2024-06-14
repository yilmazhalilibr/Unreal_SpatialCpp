// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemObject.generated.h"

class AItem;


UCLASS(Blueprintable)
class UNREAL_SPATIALCPP_API AItemObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemObject();

	//Get dimensions of the item
	UFUNCTION(BlueprintCallable)
	FIntPoint GetDimensions() { return Dimensions; }

	UFUNCTION(BlueprintCallable)
	void GetIcon(UMaterialInterface*& _icon);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Properties")
	FIntPoint Dimensions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Properties")
	UMaterialInterface* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Properties")
	UMaterialInterface* IconRotated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Item Properties")
	TSubclassOf<AItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	bool Rotated;


};
