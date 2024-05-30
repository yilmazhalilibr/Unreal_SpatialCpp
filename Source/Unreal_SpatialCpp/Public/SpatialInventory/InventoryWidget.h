// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySubsystem.h"
#include "InventoryWidget.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	float TileSize;

private:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeInventoryWidget();



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UBorder* BackgroundBorder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UBackgroundBlur* BackgroundBlur;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UInventoryGridWidget* GridWidget;

public:


};
