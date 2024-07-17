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

	UFUNCTION()
	UFSMBase* HandleChangeLogic();


	UFUNCTION()
	UFSMBase* GetCurrentState() const { return CurrentState; }

public:

	UPROPERTY()
	bool OnPossesDone = false;

	UPROPERTY()
	bool OnWarMode = false;

	UFUNCTION()
	void AILogicTick(float DeltaTime);

	UPROPERTY()
	UFSMBase* CurrentState;

	UFUNCTION()
	void ChangeStateAI(UFSMBase* NewState);

	UPROPERTY()
	UFSMStateIdle* IdleState;

	UPROPERTY()
	UFSMStateWalk* WalkState;

	UPROPERTY()
	UFSMStateRun* RunState;

	UPROPERTY()
	UFSMStateAttack* AttackState;

	UPROPERTY()
	UFSMStateChase* ChaseState;

	UPROPERTY()
	UFSMStateCover* CoverState;

	UPROPERTY()
	UFSMStatePatrol* PatrolState;


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
