// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterAiShooter.h"
#include "FSMBase.h"
#include "FSMStateIdle.h"
#include "FSMStateWalk.h"
#include "FSMStateRun.h"
#include "FSMStateAttack.h"


// Sets default values
AMasterAiShooter::AMasterAiShooter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentState = CreateDefaultSubobject<UFSMBase>(TEXT("CurrentState"));
	CurrentState->SetParameters(this);

	IdleState = CreateDefaultSubobject<UFSMStateIdle>(TEXT("IdleState"));
	WalkState = CreateDefaultSubobject<UFSMStateWalk>(TEXT("WalkState"));
	RunState = CreateDefaultSubobject<UFSMStateRun>(TEXT("RunState"));
	AttackState = CreateDefaultSubobject<UFSMStateAttack>(TEXT("AttackState"));


}

// Called when the game starts or when spawned
void AMasterAiShooter::BeginPlay()
{
	Super::BeginPlay();

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

void AMasterAiShooter::ChangeStateBP(FString _state)
{
	if (_state == "Idle")
	{
		ChangeState(IdleState);

	}
	else if (_state == "Walk")
	{
		ChangeState(WalkState);
	}
	else if (_state == "Run")
	{
		ChangeState(RunState);
	}
	else if (_state == "Attack")
	{
		ChangeState(AttackState);
	}



}

