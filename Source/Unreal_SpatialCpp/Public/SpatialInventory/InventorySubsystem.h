// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventorySubsystem.generated.h"

USTRUCT(BlueprintType)
struct FSLine
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Y;

	// Getter fonksiyonlarý
	float GetXStart() const { return X.X; }
	float GetXEnd() const { return X.Y; }
	float GetYStart() const { return Y.X; }
	float GetYEnd() const { return Y.Y; }
	// Setter fonksiyonlarý
	void SetXStart(float Value) { X.X = Value; }
	void SetXEnd(float Value) { X.Y = Value; }
	void SetYStart(float Value) { Y.X = Value; }
	void SetYEnd(float Value) { Y.Y = Value; }

};

USTRUCT(BlueprintType)
struct FSTile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Y;
};

UCLASS()
class UNREAL_SPATIALCPP_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	//Constructor
	void InventorySubsystem();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory System")
	int Columns = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory System")
	int Rows = 5;

public:
	//Getters and Setters
	UFUNCTION(BlueprintCallable)
	int GetColumns() const { return Columns; }
	UFUNCTION(BlueprintCallable)
	int GetRows() const { return Rows; }
	UFUNCTION(BlueprintCallable)
	void SetColumns(int Value) { Columns = Value; }
	UFUNCTION(BlueprintCallable)
	void SetRows(int Value) { Rows = Value; }

};



