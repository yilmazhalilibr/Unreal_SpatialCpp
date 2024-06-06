// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUW.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API UInventoryUW : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FLinearColor LineColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float LineTickness;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CreateLineSegments();

protected:
	virtual void NativeConstruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;


	//Getters and Setters
public:

	/*Avantajlar� FORCEINLINE
					Performans: K���k ve s�k kullan�lan i�levlerin sat�r i�i olmas�, i�lev �a�r�s� s�ras�nda olu�an y�k� azaltarak performans� art�r�r.
					Okunabilirlik: K���k i�levleri sat�r i�i yaparak, kodun okunabilirli�ini art�r�r.
	Dezavantajlar�
					Kod �i�kinli�i: �ok b�y�k veya nadiren kullan�lan i�levler sat�r i�i yap�l�rsa, bu kodun �i�mesine ve ikili dosyan�n b�y�mesine neden olabilir.
					Derleyici Kararlar�: Derleyici her zaman FORCEINLINE direktifini dikkate almaz ve bu i�levi sat�r i�i yapmayabilir.*/

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


private:
	UPROPERTY(meta = (BindWidget))
	class UBorder* GridBorder;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GridCanvasPanel;

	TArray<FVector2D> LineSegments;

};
