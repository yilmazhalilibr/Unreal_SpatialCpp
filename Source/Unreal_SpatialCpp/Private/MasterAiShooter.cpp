// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterAiShooter.h"
#include "MasterAiController.h"
#include "FSMBase.h"
#include "FSMStateIdle.h"
#include "FSMStateWalk.h"
#include "FSMStateRun.h"
#include "FSMStateAttack.h"
#include "FSMStateChase.h"


// Sets default values
AMasterAiShooter::AMasterAiShooter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMasterAiController::StaticClass();





}

// Called when the game starts or when spawned
void AMasterAiShooter::BeginPlay()
{
	Super::BeginPlay();


	//Set default controller
	//MasterAiController = CreateDefaultSubobject<AMasterAiController>(TEXT("MasterAiController"));

	MasterAiController = NewObject<AMasterAiController>(this);

	CurrentState = NewObject<UFSMBase>(this);
	IdleState = NewObject<UFSMStateIdle>(this);
	WalkState = NewObject<UFSMStateWalk>(this);
	RunState = NewObject<UFSMStateRun>(this);
	AttackState = NewObject<UFSMStateAttack>(this);
	ChaseState = NewObject<UFSMStateChase>(this);

	//Set default controller



	CurrentState = IdleState;
	CurrentState->Enter();


}

// Called every frame
void AMasterAiShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState)
	{
		CurrentState->Update(DeltaTime);
	}
}

// Called to bind functionality to input
void AMasterAiShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMasterAiShooter::ChangeState(UFSMBase* NewState)
{
	if (CurrentState)
	{
		CurrentState->Exit();
	}

	CurrentState = NewState;

	if (CurrentState)
	{
		CurrentState->Enter();
	}
}

void AMasterAiShooter::ChangeStateBP(EState _state)
{
	switch (_state)
	{
	case EState::Idle:
		ChangeState(IdleState);
		break;
	case EState::Walk:
		ChangeState(WalkState);
		break;
	case EState::Run:
		ChangeState(RunState);
		break;
	case EState::Attack:
		ChangeState(AttackState);
		break;
	case EState::Chase:
		ChangeState(ChaseState);
		break;

	default:
		break;
	}

}

void AMasterAiShooter::SetPerceptionProperties(float& _sightRadius, float& _sightLoseRadius, float& _peripheralVisionAngleDegrees)
{
	_sightRadius = SightRadius;
	_sightLoseRadius = SightLoseRadius;
	_peripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Perception  : %f "), SightRadius));

}

