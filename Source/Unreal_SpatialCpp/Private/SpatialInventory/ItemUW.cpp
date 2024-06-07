// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/ItemUW.h"

void UItemUW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	float DimeX = ItemObject->GetDimensions().X * TileSize;
	float DimeY = ItemObject->GetDimensions().Y * TileSize;

	Size = FVector2D(DimeX, DimeY);


}
