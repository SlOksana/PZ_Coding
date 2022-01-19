// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PZ_Coding : ModuleRules
{
	public PZ_Coding(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
