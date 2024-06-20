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

	UFUNCTION(BlueprintCallable)
	void SetAllSettings(FIntPoint _dimensions, UMaterialInterface* _icon, UMaterialInterface* _iconRotated, TSubclassOf<AItem> _itemClass, bool _rotated);

	UFUNCTION(BlueprintCallable)
	void GetAllSettings(FIntPoint& _dimensions, UMaterialInterface*& _icon, UMaterialInterface*& _iconRotated, TSubclassOf<AItem>& _itemClass, bool& _rotated);

	// Getter for ItemClass
	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	TSubclassOf<AItem> GetItemClass() const;

	// Setter for ItemClass
	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	void SetItemClass(TSubclassOf<AItem> NewItemClass);

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
