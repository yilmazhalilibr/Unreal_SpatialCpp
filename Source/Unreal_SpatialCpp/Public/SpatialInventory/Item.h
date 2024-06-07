// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventorySubsystem.h"

#include "Item.generated.h"

class UItemObject;
class UStaticMeshComponent;
class USphereComponent;
class USceneComponent;
class UInventorySubsystem;

UCLASS()
class UNREAL_SPATIALCPP_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//add uscene component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	//add static mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	//Add collision component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* CollisionComponent;

	//Add ItemObject reference
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UItemObject* ItemObject;

	UPROPERTY()
	UInventorySubsystem* InventorySubsystem;

	//Add OnComponentBeginOverlap function
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public:
	// Called every frame	
	virtual void Tick(float DeltaTime) override;

	//Function to set the ItemObject reference
	void SetItemObject(UItemObject* NewItemObject);
	//get the ItemObject reference
	UItemObject* GetItemObject() { return ItemObject; }

	//virtual UItemObject* GetDefaultItemObject();

	UFUNCTION(BlueprintImplementableEvent, Category = "Item Class", meta = (DisplayName = "GetDefaultItemObject"),BlueprintCallable)
	UItemObject* GetDefaultItemObject_Implementation();
};
