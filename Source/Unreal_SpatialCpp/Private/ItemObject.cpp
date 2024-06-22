#include "ItemObject.h"

// Sets default values
AItemObject::AItemObject()
{
	// Set this actor to call Tick() every frame.  
	PrimaryActorTick.bCanEverTick = true;
	ItemClass = nullptr; // Initialize ItemClass to nullptr
}

// Getter for ItemClass
TSubclassOf<AItem> AItemObject::GetItemClass() const
{
	return ItemClass;
}

// Setter for ItemClass
void AItemObject::SetItemClass(TSubclassOf<AItem> NewItemClass)
{
	ItemClass = NewItemClass;
}

FIntPoint AItemObject::GetDimensions() const
{
	if (Rotated)
	{
		return FIntPoint(Dimensions.Y, Dimensions.X);
	}
	else
	{
		return Dimensions;
	}

}

// GetIcon implementation
void AItemObject::GetIcon(UMaterialInterface*& _icon)
{
	_icon = Icon;
}

// SetAllSettings implementation
void AItemObject::SetAllSettings(FIntPoint _dimensions, UMaterialInterface* _icon, UMaterialInterface* _iconRotated, TSubclassOf<AItem> _itemClass, bool _rotated)
{
	Dimensions = _dimensions;
	Icon = _icon;
	IconRotated = _iconRotated;
	ItemClass = _itemClass;
	Rotated = _rotated;
}

// GetAllSettings implementation
void AItemObject::GetAllSettings(FIntPoint& _dimensions, UMaterialInterface*& _icon, UMaterialInterface*& _iconRotated, TSubclassOf<AItem>& _itemClass, bool& _rotated)
{
	_dimensions = Dimensions;
	_icon = Icon;
	_iconRotated = IconRotated;
	_itemClass = ItemClass;
	_rotated = Rotated;
}
