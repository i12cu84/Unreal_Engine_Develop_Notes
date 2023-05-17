// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class cpp3dp : ModuleRules
{
	public cpp3dp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
