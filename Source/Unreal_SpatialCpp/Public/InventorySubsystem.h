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
	int GetColumns() { return Columns; }

	UFUNCTION(BlueprintCallable)
	int GetRows() { return Rows; }

	UFUNCTION(BlueprintCallable)
	void SetColumns(int _columns) { Columns = _columns; }

	UFUNCTION(BlueprintCallable)
	void SetRows(int _rows) { Rows = _rows; }


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Widget Initialize")
	int32 Rows;


};
