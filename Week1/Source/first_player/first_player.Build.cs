// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class first_player : ModuleRules
{
	public first_player(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
