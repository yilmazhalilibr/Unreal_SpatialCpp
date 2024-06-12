// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventorySubsystem.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void SetupInventory(int _columns, int _rows, float _tileSize, FLinearColor _lineColor, float _lineThickness)
	{
		Columns = _columns;
		Rows = _rows;
		TileSize = _tileSize;
		LineColor = _lineColor;
		LineThickness = _lineThickness;
	}


	UFUNCTION(BlueprintCallable)
	int GetColumns() { return Columns; }

	UFUNCTION(BlueprintCallable)
	int GetRows() { return Rows; }

	UFUNCTION(BlueprintCallable)
	void SetColumns(int _columns) { Columns = _columns; }

	UFUNCTION(BlueprintCallable)
	void SetRows(int _rows) { Rows = _rows; }

	UFUNCTION(BlueprintCallable)
	void SetTileSize(float _tileSize) { TileSize = _tileSize; }

	UFUNCTION(BlueprintCallable)
	void SetLineColor(FLinearColor _lineColor) { LineColor = _lineColor; }

	UFUNCTION(BlueprintCallable)
	void SetLineThickness(float _lineThickness) { LineThickness = _lineThickness; }

	UFUNCTION(BlueprintCallable)
	float GetTileSize() { return TileSize; }

	UFUNCTION(BlueprintCallable)
	FLinearColor GetLineColor() { return LineColor; }

	UFUNCTION(BlueprintCallable)
	float GetLineThickness() { return LineThickness; }


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	FLinearColor LineColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	float LineThickness = 1.0f;

};
