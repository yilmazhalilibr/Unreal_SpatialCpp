// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "ItemObject.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "TimerManager.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/Texture2D.h"
#include "Brushes/SlateImageBrush.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"


void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Refresh.AddDynamic(this, &UItemWidget::OnRefreshHandle);

}

void UItemWidget::NativeDestruct()
{
	Super::NativeDestruct();

	//ItemImage->BrushDelegate.Unbind();
	Refresh.Clear();
}

void UItemWidget::InitializeWidget(AItemObject* _itemObject, float _tileSize)
{
	ItemObject = _itemObject;
	TileSize = _tileSize;
	_itemObject->GetIcon(IconMaterial);

	//ILERIDE BURAYA ENVANTER YUKLENIRKEN - YUKLENMEYI BELLI EDEN BIR HAREKETLI IKON KOYALIM


	//.1 saniye sonra refresh eventini tetikle ve tetiklerken Lambda kullan ve delegate i tetikle
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
		Refresh.Broadcast();

		}, 0.1f, false);

	if (ItemImage)
	{
		//ItemImage->SetBrushFromTexture(nullptr); // Ýlk baþta boþ bir texture atayabilirsiniz
		//ItemImage->BrushDelegate.BindUFunction(this, "GetIconImage");
		GetIconImage();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemImage is nullptr(ItemWidget.cpp) ...InitializeWidget"));
	}

}

void UItemWidget::OnRefreshHandle()
{
	if (ItemObject)
	{
		auto _dimensions = ItemObject->GetDimensions();

		float _width = _dimensions.X * TileSize;
		float _height = _dimensions.Y * TileSize;
		Size.X = _width;
		Size.Y = _height;

		if (BackgroundSizeBox)
		{
			BackgroundSizeBox->SetWidthOverride(_width);
			BackgroundSizeBox->SetHeightOverride(_height);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BackgroundSizeBox is nullptr"));
		}

		if (ItemImage)
		{
			auto itemSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot);
			if (itemSlot)
			{
				itemSlot->SetSize(FVector2D(_width, _height));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ItemImage is not in a CanvasPanelSlot"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ItemImage is nullptr. Satýr : 87"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemObject is nullptr (ItemWidget.cpp) : Satýr 92"));
	}
}

void UItemWidget::GetIconImage()
{
	//if (ItemObject)
	//{
	//	UMaterialInterface* Material = nullptr;
	//	ItemObject->GetIcon(Material);

	//	//Materil'in ismini ve dosya olunu LOG'a yazdýrýr
	//	/*UE_LOG(LogTemp, Warning, TEXT("Material Name : %s"), *Material->GetName());
	//	UE_LOG(LogTemp, Warning, TEXT("Material Path : %s"), *Material->GetPathName());*/

	//	if (Material)
	//	{
	//		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

	//		if (DynamicMaterial)
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("DynamicMaterial is created"));
	//		}

	//		FSlateBrush Brush;
	//		Brush.SetResourceObject(DynamicMaterial);
	//		Brush.DrawAs = ESlateBrushDrawType::Image;
	//		Brush.ImageSize = FVector2D(Size.X, Size.Y);


	//		if (ItemImage)
	//		{
	//			ItemImage->SetBrush(Brush);
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("ItemImage is nullptr(ItemWidget.cpp)"));
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Icon is nullptr(ItemWidget.cpp)"));
	//	}
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("ItemObject is nullptr(ItemWidget.cpp)"));
	//}

	if (ItemObject)
	{
		UMaterialInterface* _icon;
		ItemObject->GetIcon(_icon);

		if (_icon)
		{
			// Material kullanarak FSlateBrush olu�turma
			FSlateBrush* _brush = new FSlateBrush();
			_brush->SetResourceObject(_icon);
			_brush->ImageSize = FVector2D(Size.X, Size.Y);
			// _brush->TintColor = FSlateColor(FLinearColor::White); // Gerekirse renk tonu ekleyin

			if (ItemImage)
			{
				ItemImage->SetBrush(*_brush);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ItemImage is nullptr(ItemWidget.cpp)"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Icon is nullptr(ItemWidget.cpp)"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemObject is nullptr(ItemWidget.cpp)"));
	}

}

