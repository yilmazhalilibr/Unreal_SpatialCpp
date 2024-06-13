// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryStructures.generated.h"


USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_USTRUCT_BODY()

	FVector2D Start;
	FVector2D End;
};

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_USTRUCT_BODY()

	int X;
	int Y;
};




UCLASS()
class UNREAL_SPATIALCPP_API AInventoryStructures : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventoryStructures();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


};
