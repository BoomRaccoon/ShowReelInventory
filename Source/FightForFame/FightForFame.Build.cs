// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FightForFame : ModuleRules
{
	public FightForFame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
					new string[] {
						"FightForFame"
					}
				);

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"MotionWarping",
			"AIModule",
			"UMG",
			"Slate"
		});
	}
}
