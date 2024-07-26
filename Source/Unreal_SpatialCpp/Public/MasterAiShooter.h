// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
//#include "/Users/DBK Games 05/Documents/Unreal Projects/Unreal_SpatialCpp/Plugins/ALS/Source/ALSV4_CPP/Public/Character/ALSCharacter.h"
#include "ALSV4_CPP/Public/Character/ALSCharacter.h"
#include "MasterAiShooter.generated.h"



DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAiOnDead, AMasterAiShooter*, bool bDead);


class AMasterAiSpawner;
class AMasterAiController;
class UFSMBase;
class UFSMStateIdle;
class UFSMStateWalk;
class UFSMStateRun;
class UFSMStateAttack;
class UFSMStateChase;
class UFSMStateCover;
class UFSMStatePatrol;
class UFSMStateDead;
class UFSMStateSearch;
class UFSMStateResetAI;
class UFSMStateHeard;


UENUM(BlueprintType)
enum class EState : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Chase,
	Cover,
	Patrol,
	Dead,
	Search,
	ResetAI,
	Heard
};


UCLASS()
class UNREAL_SPATIALCPP_API AMasterAiShooter : public AALSCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	 // Sets default values for this character's properties
	AMasterAiShooter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Destruct event
	virtual void Destroyed() override;

	UFUNCTION()
	void OnTakeAIAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	FOnAiOnDead OnAiDead;

	UFUNCTION(BlueprintCallable)
	void SetSpawner(AMasterAiSpawner* _spawner) { MasterAiSpawner = _spawner; }

	UFUNCTION(BlueprintCallable)
	AMasterAiSpawner* GetSpawner() const { return MasterAiSpawner; }


	// AI Properties
public:
	UFUNCTION(BlueprintCallable)
	float GetChaseDistance() const { return ChaseDistance; }

	UFUNCTION()
	float GetAttackDistance() const { return AttackDistance; }

	UFUNCTION()
	float GetMaxHP() const { return MaxHP; }

	UFUNCTION()
	float GetCurrentHP() const { return CurrentHP; }

	// AI Properties Getters
	UFUNCTION()
	float GetSightRadius() const { return SightRadius; }

	UFUNCTION()
	float GetSightLoseRadius() const { return SightLoseRadius; }

	UFUNCTION()
	float GetPeripheralVisionAngleDegrees() const { return PeripheralVisionAngleDegrees; }

	UFUNCTION()
	float GetPatrolRadius() const { return PatrolRadius; }

	UFUNCTION()
	FVector GetSpawnLocation() const { return SpawnLocation; }

	UFUNCTION()
	float GetPatrolTime() const { return PatrolTime; }

	UFUNCTION()
	float GetDeadDestroyTime() const { return DeadDestroyTime; }

	UFUNCTION()
	float GetSuspicionTime() const { return SuspicionTime; }

	UFUNCTION()
	float GetPlayerLostTime() const { return PlayerLostTime; }

	UFUNCTION()
	bool GetAIDead() const { return AIDead; }

	UFUNCTION()
	void DealDamage(float Damage);

public:
	UPROPERTY()
	AMasterAiSpawner* MasterAiSpawner;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	AMasterAiController* MasterAiController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Properties")
	FText The_features_below_are_for_AI_Perception;
	/**AI Controller Properties*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float SightRadius = 3500.0f;

	/**AI Controller Properties (SightRadius + LoseRadius(Example:500.0f))*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float SightLoseRadius = 500.0f;

	/**AI Controller Properties*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float PeripheralVisionAngleDegrees = 120.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Properties")
	FText The_following_features_are_the_features_of_AI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float ChaseDistance = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float AttackDistance = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float CurrentHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float PatrolRadius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float PatrolTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float DeadDestroyTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float SuspicionTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	float PlayerLostTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Properties")
	bool AIDead = false;


private:
	UPROPERTY()
	FVector SpawnLocation;
};
