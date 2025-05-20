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
            "ControlRig", // For RigUnit_SphereTraceByTraceProfile
            "RigVM", // For RigUnit_SphereTraceByTraceProfile
            "PhysicsControl", // For ExtendedPhysicsControl
            "ProceduralMeshComponent", // For UExtendedUnrealLibrary::ProceduralMesh_SetUseComplexAsSimpleCollision
        });
			
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
            "NetCore", // ExtendedArrayLibrary uses this for "MARK_PROPERTY_DIRTY"
			"AssetRegistry", // for UExtendedAnimationLibrary::GetAllAnimations
			"RHI", // for UExtendedUnrealLibrary::ClearRenderTargetCube

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
