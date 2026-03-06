// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEDemo : ModuleRules
{
	public UEDemo(ReadOnlyTargetRules Target) : base(Target)
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
			"UEDemo",
			"UEDemo/Variant_Platforming",
			"UEDemo/Variant_Platforming/Animation",
			"UEDemo/Variant_Combat",
			"UEDemo/Variant_Combat/AI",
			"UEDemo/Variant_Combat/Animation",
			"UEDemo/Variant_Combat/Gameplay",
			"UEDemo/Variant_Combat/Interfaces",
			"UEDemo/Variant_Combat/UI",
			"UEDemo/Variant_SideScrolling",
			"UEDemo/Variant_SideScrolling/AI",
			"UEDemo/Variant_SideScrolling/Gameplay",
			"UEDemo/Variant_SideScrolling/Interfaces",
			"UEDemo/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
