// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "MasterAiSpawner.generated.h"

class AMasterAiShooter;
class AMasterAiController;


UCLASS()
class UNREAL_SPATIALCPP_API AMasterAiSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMasterAiSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Master AI")
	void SpawnMasterAi(int _spawnCount);

	//Master Ai Spawn List
	UPROPERTY(BlueprintReadOnly, Category = "Master AI")
	TArray<AMasterAiShooter*> MasterAiSpawnedList;

	UFUNCTION()
	void DeadMasterAi(AMasterAiShooter* _deadAi, bool _dead);

	/**Select Master Ai Shooter Blueprint class*/
	UPROPERTY(EditAnywhere, Category = "Master AI")
	TSubclassOf<AMasterAiShooter> BPMasterAiShooterClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//We need all EQS system remote controlled here in the AI's states.

	UFUNCTION()
	void WarningPlayerDetected(bool _isDetected);

	UPROPERTY()
	TMap<AMasterAiShooter*, FVector> AttackCordinates;

	UPROPERTY()
	TMap<AMasterAiShooter*, FVector> CoverCordinates;

	UFUNCTION()
	FVector GetAttackCordinate(AMasterAiShooter* _ai);

	UFUNCTION()
	FVector GetCoverCordinate(AMasterAiShooter* _ai);

	UFUNCTION()
	void HandleAttackCordinateToCover(FName _eqsName);
private:
	void ExecuteEQS(FName _eqsName);
	/**Write first EQS Name Example -> Attack  ,as second select EQS node*/
	UPROPERTY(EditAnywhere, Category = "Master AI")
	TMap<FName, UEnvQuery*> QueryMap;



};
