// Copyright 2023 Dream Seed LLC.

using UnrealBuildTool;

public class ExtendedUnreal : ModuleRules
{
	public ExtendedUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[]
		{
		});
				
		
		PrivateIncludePaths.AddRange(new string[]
		{
		});
			
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
            "GameplayTags",
			"GameplayAbilities",
		});
			
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
            "NetCore", // ExtendedArrayLibrary uses this for "MARK_PROPERTY_DIRTY"
		});

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "UnrealEd",
            });
        }


        DynamicallyLoadedModuleNames.AddRange(new string[]
		{
		});
	}
}
