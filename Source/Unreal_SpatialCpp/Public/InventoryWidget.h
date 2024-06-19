// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryStructures.h"
#include "ItemWidget.h"
#include "InventoryWidget.generated.h"

/**
 *
 */

class UCanvasPanel;
class UBorder;
class UBackgroundBlur;
class UInventoryGridWidget;
class UInventorySubsystem;
class FReply;


UCLASS()
class UNREAL_SPATIALCPP_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	//Event On Initialized Widget

public:
	virtual void NativeConstruct() override;

	



	UPROPERTY()
	UInventorySubsystem* InventorySubsystem;

	//Getter Inventory Grid Widget
	UFUNCTION(BlueprintCallable)
	UInventoryGridWidget* GetGrid() { return InventoryGrid; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UInventoryGridWidget* InventoryGrid;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TSubclassOf<UItemWidget> BP_ItemWidget;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UItemWidget> GetItemWidget() { return BP_ItemWidget; }

	//Bind backgrund border mouse down event



protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


	//Bind Canvas panel
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> BackgroundBorder;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> BackgroundBlur;





};
