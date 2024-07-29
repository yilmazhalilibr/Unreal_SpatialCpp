// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/Character.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "MasterAiController.generated.h"

/**
 *
 */

class AMasterAiShooter;
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


UCLASS()
class UNREAL_SPATIALCPP_API AMasterAiController : public AAIController
{
	GENERATED_BODY()


protected:
	//constructor 
	AMasterAiController();

	virtual void BeginPlay() override;
	//tick
	virtual void Tick(float DeltaTime) override;

	//OnPosses override
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool bIsPlayerDetected = false;

	UPROPERTY()
	bool bPawnLowHasLowHp = false;

	UPROPERTY()
	bool bIsPlayerInAttackRange = false;

	UPROPERTY()
	FVector PlayerLastLocation;



	UFUNCTION()
	UFSMBase* GetCurrentState() const { return CurrentState; }



public:

	UPROPERTY()
	bool OnPossesDone = false;

	UPROPERTY()
	bool OnWarMode = false;

	UPROPERTY()
	bool bSuspicion = true;

	UPROPERTY()
	float bSuspicionTimer = 0.0f;

	UPROPERTY()
	bool bMissingPlayer = false;

	UPROPERTY()
	float bMissingPlayerTimer = 0.0f;

	UPROPERTY()
	bool bAiInSearch = false;

	UPROPERTY()
	bool bSearchDoOnce = false;

	UPROPERTY()
	bool bIsPlayerHeard = false;

	UPROPERTY()
	FVector bLastHeardLocation = FVector().Zero();

	UFUNCTION()
	void AILogicTick(float DeltaTime);
	UFUNCTION()
	UFSMBase* HandleChangeLogic();

	UPROPERTY()
	UFSMBase* CurrentState;

	UFUNCTION(BlueprintCallable)
	void ChangeStateAI(UFSMBase* NewState);

	UFUNCTION()
	FVector GetPlayerLastLocation() const { return PlayerLastLocation; }

	UFUNCTION()
	void SetOnWarMode(bool Value) { OnWarMode = Value; }

	UFUNCTION()
	void SetInAttackRange(bool Value) { bIsPlayerInAttackRange = Value; }

	UFUNCTION()
	void SetAiInSearch(bool Value) { bAiInSearch = Value; }

	UFUNCTION()
	FVector GetLastHeardLocation() const { return bLastHeardLocation; }

	UFUNCTION()
	bool GetIsPlayerHeard() const { return bIsPlayerHeard; }

	UFUNCTION()
	void SetIsPlayerHeard(bool Value) { bIsPlayerHeard = Value; }

	UPROPERTY(BlueprintReadOnly)
	UFSMStateIdle* IdleState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStateWalk* WalkState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStateRun* RunState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStateAttack* AttackState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStateChase* ChaseState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStateCover* CoverState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStatePatrol* PatrolState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStateDead* DeadState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStateSearch* SearchState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStateResetAI* ResetAIState;

	UPROPERTY(BlueprintReadOnly)
	UFSMStateHeard* HeardState;

private:


	UPROPERTY()
	AMasterAiShooter* AiShooter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAISenseConfig_Sight* SightConfig;

	//Sound perception
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAISenseConfig_Hearing* HearingConfig;

	//Damage perceiption
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAISenseConfig_Damage* DamageConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	UFSMBase* HandleFSM(UFSMBase* NewFSM);

};
