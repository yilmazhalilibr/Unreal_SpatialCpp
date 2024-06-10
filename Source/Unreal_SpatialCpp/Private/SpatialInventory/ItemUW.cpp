// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/ItemUW.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"


void UItemUW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	float DimeX = ItemObject->GetDimensions().X * TileSize;
	float DimeY = ItemObject->GetDimensions().Y * TileSize;

	Size = FVector2D(DimeX, DimeY);

	if (BackgroundSizeBox)
	{
		BackgroundSizeBox->SetWidthOverride(DimeX);
		BackgroundSizeBox->SetHeightOverride(DimeY);
	}
	if (ItemImage)
	{

		UCanvasPanelSlot* ItemCanvasSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot);
		ItemCanvasSlot->SetSize(FVector2D(DimeX, DimeY));

	}

	ItemImage->BrushDelegate.BindUFunction(this, FName("GetIconImage"));

}

UMaterialInterface* UItemUW::GetIconImage()
{
	if (ItemObject)
	{
		// UMaterialInstanceDynamic nesnesi oluþturma
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(ItemObject->GetIconImage(), this);

		// FSlateBrush oluþturma ve materyali ayarlama
		FSlateBrush Brush;
		Brush.SetResourceObject(DynamicMaterial);
		Brush.ImageSize = FVector2D(Size.X, Size.Y); // Ýsteðe baðlý olarak boyutu ayarlayýn

		// UImage widget'ýna brush uygulama
		ItemImage->SetBrush(Brush);

		return DynamicMaterial;
	}

	return nullptr;
}
