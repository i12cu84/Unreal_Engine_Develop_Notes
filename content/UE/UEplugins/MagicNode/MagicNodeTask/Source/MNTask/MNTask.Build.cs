// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MNTask : ModuleRules
{
	public MNTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "MagicNodeRuntime" });
	}
}
