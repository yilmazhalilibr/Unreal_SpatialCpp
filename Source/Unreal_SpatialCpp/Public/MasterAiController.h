// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/Character.h"
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
	void SetAiInSearch(bool Value) { bAiInSearch = Value; }

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

private:
	UPROPERTY()
	AMasterAiShooter* AiShooter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAISenseConfig_Sight* SightConfig;


	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


};
