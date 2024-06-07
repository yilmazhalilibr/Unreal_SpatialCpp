// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialInventory/Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "SpatialInventory/ItemObject.h"
#include "GameFramework/Actor.h"
#include "SpatialInventory/InventorySubsystem.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Make the Scene Component the Root Component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;

	//Make root component the Mesh Component and attach the Sphere Component to it
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComponent->SetupAttachment(SceneComponent);

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->SetupAttachment(MeshComponent);

	//Mesh Component Collision Settings No Collision
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//AddDynamic to the OnComponentBeginOverlap function
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnComponentBeginOverlap);

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();


	/*if (ItemObject == nullptr)
	{
		auto item = GetDefaultItemObject();
		SetItemObject(item);
	}*/

	InventorySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>();

}

void AItem::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if the OtherActor is a player
	if (OtherActor->ActorHasTag("Player"))
	{
		if (ItemObject->GetItemData().Dimensions.X <= InventorySubsystem->GetInventories().Find("PlayerInventory")->InventoryColumn)
		{
			//BURASI ILERIDE DEÐÝÞECEK ÇÜNKÜ PLAYER INVENTORY NAME SABÝT OLARAK KALMAYACAK
			if (InventorySubsystem->TryAddItemToInventory("PlayerInventory", ItemObject, 1))
			{
				UE_LOG(LogTemp, Warning, TEXT("Item added to inventory!"));
				Destroy();
				return;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Inventory is full!"));
			}
			//Destroy the item
			Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory is full!"));
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not a player!"));
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::SetItemObject(UItemObject* NewItemObject)
{
	ItemObject = NewItemObject;
}

//UItemObject* AItem::GetDefaultItemObject()
//{
//	return nullptr;
//}




