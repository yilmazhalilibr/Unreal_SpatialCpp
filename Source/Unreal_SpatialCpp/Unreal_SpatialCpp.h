// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUnreal_SpatialCppModule : public IModuleInterface
{
	// IModuleInterface implementation
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};