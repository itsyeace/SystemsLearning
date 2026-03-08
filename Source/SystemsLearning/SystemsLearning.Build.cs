// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SystemsLearning : ModuleRules
{
	public SystemsLearning(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SystemsLearning",
			"SystemsLearning/Variant_Platforming",
			"SystemsLearning/Variant_Platforming/Animation",
			"SystemsLearning/Variant_Combat",
			"SystemsLearning/Variant_Combat/AI",
			"SystemsLearning/Variant_Combat/Animation",
			"SystemsLearning/Variant_Combat/Gameplay",
			"SystemsLearning/Variant_Combat/Interfaces",
			"SystemsLearning/Variant_Combat/UI",
			"SystemsLearning/Variant_SideScrolling",
			"SystemsLearning/Variant_SideScrolling/AI",
			"SystemsLearning/Variant_SideScrolling/Gameplay",
			"SystemsLearning/Variant_SideScrolling/Interfaces",
			"SystemsLearning/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
