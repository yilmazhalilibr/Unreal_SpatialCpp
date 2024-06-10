// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUW.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoved, UItemObject*, Item);

class UInventorySubsystem;

UCLASS()
class UNREAL_SPATIALCPP_API UInventoryUW : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	int32 Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	int32 Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	FLinearColor LineColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	float LineTickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	FName InventoryName;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CreateLineSegments();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnRemoved OnRemoved;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void EventOnRemoved(UItemObject* Item);

protected:
	virtual void NativeConstruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;


	//Getters and Setters
public:

	/*Avantajlarý FORCEINLINE
					Performans: Küçük ve sýk kullanýlan iþlevlerin satýr içi olmasý, iþlev çaðrýsý sýrasýnda oluþan yükü azaltarak performansý artýrýr.
					Okunabilirlik: Küçük iþlevleri satýr içi yaparak, kodun okunabilirliðini artýrýr.
	Dezavantajlarý
					Kod Þiþkinliði: Çok büyük veya nadiren kullanýlan iþlevler satýr içi yapýlýrsa, bu kodun þiþmesine ve ikili dosyanýn büyümesine neden olabilir.
					Derleyici Kararlarý: Derleyici her zaman FORCEINLINE direktifini dikkate almaz ve bu iþlevi satýr içi yapmayabilir.*/

	FORCEINLINE void SetColumn(int32 InColumn) { Column = InColumn; }
	FORCEINLINE int32 GetColumn() const { return Column; }

	FORCEINLINE void SetRow(int32 InRow) { Row = InRow; }
	FORCEINLINE int32 GetRow() const { return Row; }

	FORCEINLINE void SetTileSize(float InTileSize) { TileSize = InTileSize; }
	FORCEINLINE float GetTileSize() const { return TileSize; }

	FORCEINLINE void SetLineColor(FLinearColor InLineColor) { LineColor = InLineColor; }
	FORCEINLINE FLinearColor GetLineColor() const { return LineColor; }

	FORCEINLINE void SetLineTickness(float InLineTickness) { LineTickness = InLineTickness; }
	FORCEINLINE float GetLineTickness() const { return LineTickness; }

	UFUNCTION(BlueprintCallable, Category = "Widget Initialize")
	FORCEINLINE void InitializeWD(int32 InColumn, int32 InRow, float InTileSize, FLinearColor InLineColor, float InLineTickness)
	{
		Column = InColumn;
		Row = InRow;
		TileSize = InTileSize;
		LineColor = InLineColor;
		LineTickness = InLineTickness;
	}


	UFUNCTION(BlueprintCallable, Category = "Widget Initialize")
	TMap<UItemObject*, FTile> GetAllItems(FName InventoryName);

private:
	UPROPERTY(meta = (BindWidget))
	class UBorder* GridBorder;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GridCanvasPanel;

	UPROPERTY()
	TArray<FVector2D> LineSegments;

	UFUNCTION()
	void Refresh(FName InventoryName);

	UPROPERTY()
	UInventorySubsystem* InventorySubsystem;


};
