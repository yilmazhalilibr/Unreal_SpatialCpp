// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unreal_SpatialCpp : ModuleRules
{
    public Unreal_SpatialCpp(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "GameplayTasks", "NavigationSystem", "ALSV4_CPP" });


        PrivateDependencyModuleNames.AddRange(new string[] { "ALSV4_CPP" });

    }
}
