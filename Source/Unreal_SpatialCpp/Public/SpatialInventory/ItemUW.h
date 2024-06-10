// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpatialInventory/ItemObject.h"

#include "ItemUW.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoved, UItemObject*, Item);

class UCanvasPanel;
class USizeBox;
class UBorder;
class UImage;


UCLASS()
class UNREAL_SPATIALCPP_API UItemUW : public UUserWidget
{
	GENERATED_BODY()

protected:
	//add event on initialize
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USizeBox* BackgroundSizeBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(BlueprintAssignable, Category = "Item")
	FOnRemoved OnRemoved;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnItemRemoved();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	float TileSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	UItemObject* ItemObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	FVector2D Size;

	UFUNCTION()
	UMaterialInterface* GetIconImage();
};
