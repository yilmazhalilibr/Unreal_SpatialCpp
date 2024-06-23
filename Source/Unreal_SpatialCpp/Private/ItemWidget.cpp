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
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"	
#include "Input/Reply.h"
#include "Input/Events.h"
//UDragDropOperation Header
#include "Blueprint/DragDropOperation.h"
#include <Blueprint/WidgetBlueprintLibrary.h>




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


FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	//UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDown - ItemWidget"));

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDown LeftMouseButton - ItemWidget"));

		// Drag detect işlemi başlat
		FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return EventReply.NativeReply;

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	if (BackgroundBorder)
	{
		BackgroundBorder->SetBrushColor(FLinearColor(0, 0, 0, 0.5f));
	}

}

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (BackgroundBorder)
	{
		BackgroundBorder->SetBrushColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.2f));
	}
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// DragDropOperation yarat
	UDragDropOperation* Operation = NewObject<UDragDropOperation>();
	Operation->Payload = ItemObject;
	Operation->DefaultDragVisual = this;
	Operation->Pivot = EDragPivot::CenterCenter;

	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragDetected - ItemWidget@"));

	// Parent'ten kaldır
	RemoveFromParent();

	OutOperation = Operation;
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

	//	Materil'in ismini ve dosya olunu LOG'a yazdýrýr
	//	/*UE_LOG(LogTemp, Warning, TEXT("Material Name : %s"), *Material->GetName());
	//	UE_LOG(LogTemp, Warning, TEXT("Material Path : %s"), *Material->GetPathName());*/

	//		if (Material)
	//		{
	//			UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

	//			if (DynamicMaterial)
	//			{
	//				UE_LOG(LogTemp, Warning, TEXT("DynamicMaterial is created"));
	//			}

	//			FSlateBrush Brush;
	//			Brush.SetResourceObject(DynamicMaterial);
	//			Brush.DrawAs = ESlateBrushDrawType::Image;
	//			Brush.ImageSize = FVector2D(Size.X, Size.Y);

	//			if (ItemImage)
	//			{
	//				//ItemImage->SetBrush(Brush);
	//				ItemImage->SetBrushFromMaterial(DynamicMaterial);

	//				//Ekrana ColorAndOpacity ve Tint color değerlerini yazdırır
	//				UE_LOG(LogTemp, Warning, TEXT("ColorAndOpacity : %s"), *ItemImage->ColorAndOpacity.ToString());

	//			}
	//			else
	//			{
	//				UE_LOG(LogTemp, Warning, TEXT("ItemImage is nullptr(ItemWidget.cpp)"));
	//			}
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("Icon is nullptr(ItemWidget.cpp)"));
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("ItemObject is nullptr(ItemWidget.cpp)"));
	//	}

	if (ItemObject)
	{
		UMaterialInterface* _icon;
		ItemObject->GetIcon(_icon);

		/*if (ItemObject->IsRotated())
		{
			double _temp = Size.X;
			Size.X = Size.Y;
			Size.Y = _temp;
		}*/

		if (_icon)
		{
			// Material kullanarak FSlateBrush olu�turma
			FSlateBrush* _brush = new FSlateBrush();
			_brush->SetResourceObject(_icon);
			_brush->ImageSize = FVector2D(Size.X, Size.Y);

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

