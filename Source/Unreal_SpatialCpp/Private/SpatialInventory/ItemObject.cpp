// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/ItemObject.h"

UItemObject::UItemObject()
{

}

UMaterialInterface* UItemObject::GetIconImage()
{
	if (ItemData.Rotated)
	{
		return ItemData.IconRotated;
	}
	return ItemData.Icon;
}
