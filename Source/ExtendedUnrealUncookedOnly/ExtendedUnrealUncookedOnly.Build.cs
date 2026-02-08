// Copyright 2025 Dream Seed LLC.

using UnrealBuildTool;

public class ExtendedUnrealUncookedOnly : ModuleRules
{
	public ExtendedUnrealUncookedOnly(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... 
				"UnrealEd",
				"BlueprintGraph",
				"KismetCompiler",
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... 
				"UnrealEd",
				"BlueprintGraph",
				"KismetCompiler",
				"Kismet",
			});
	}
}
