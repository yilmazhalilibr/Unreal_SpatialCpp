// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


class UStaticMeshComponent;
class USphereComponent;
class AItemObject;
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

	//add static mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	UStaticMeshComponent* StaticMesh;

	//add Sphere Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", Meta = (DisplayName = "ItemObject", ExposeOnSpawn = true))
	AItemObject* ItemObject;

	//Add On Component Begin Overlap Event 
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent, Category = "Item Class", meta = (DisplayName = "GetDefaultItemObject"), BlueprintCallable)
	bool GetDefaultItemObject_Implementation(AItemObject*& item);

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	UInventorySubsystem* InventorySubsystem;

};
