// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_SpatialCppGameMode.h"
#include "Unreal_SpatialCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_SpatialCppGameMode::AUnreal_SpatialCppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
