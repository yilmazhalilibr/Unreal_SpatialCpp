// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 *
 */

class UCanvasPanel;
class USizeBox;
class UImage;
class UBorder;
class AItemObject;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRefresh);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoved, AItemObject*, ItemObject);


UCLASS()
class UNREAL_SPATIALCPP_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	//Descructor
	virtual void NativeDestruct() override;

	void InitializeWidget(AItemObject* _itemObject, float _tileSize);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "ItemWidget")
	float TileSize;

	UPROPERTY(BlueprintAssignable)
	FRefresh Refresh;

	UPROPERTY(BlueprintAssignable)
	FOnRemoved OnRemoved;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "ItemWidget")
	AItemObject* ItemObject;

	UPROPERTY()
	FVector2D Size;

	UFUNCTION(BlueprintCallable)
	void OnRefreshHandle();

	UFUNCTION(BlueprintCallable)
	void GetIconImage();

	UPROPERTY()
	UMaterialInterface* IconMaterial;

	
protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> BackgroundSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;



};
