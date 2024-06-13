// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ItemObject.h"
#include "InventorySubsystem.h"



// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//add static mesh component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	//add Sphere Collision
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);

	//Static mesh component Collision NoCollision 
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);



}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnComponentBeginOverlap);


	if (!ItemObject)
	{
		//GetDefaultItemObject
		GetDefaultItemObject_Implementation(ItemObject);
		UE_LOG(LogTemp, Warning, TEXT("ItemObject - GetDefaultItemObject"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemObject is not null(Item.cpp)"));

	}
	if (!InventorySubsystem)
	{
		InventorySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>();
		UE_LOG(LogTemp, Warning, TEXT("InventorySubsystem is get it"));
	}

}

void AItem::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("Player"))
	{
		if (ItemObject)
		{
			bool success;
			InventorySubsystem->TryAddItem(ItemObject, success);

			if (success)
			{
				UE_LOG(LogTemp, Warning, TEXT("Item Added"));
				Destroy();

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Item Not Added"));
			}


		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ItemObject is null(Item.cpp)"));
		}

		//GetDefaultItemObject
	}


}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

