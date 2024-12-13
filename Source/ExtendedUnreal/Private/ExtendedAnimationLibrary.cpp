// Copyright 2023 Dream Seed LLC.


#include "ExtendedAnimationLibrary.h"


#include "Animation/BlendSpace.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimNode_LinkedAnimLayer.h"
#include "AssetRegistry/AssetRegistryModule.h"

void UExtendedAnimationLibrary::GetBlendSpaceAxisMinMax(UBlendSpace* BlendSpace, EExtendedBlendSpaceAxis Axis, double& Min, double& Max)
{
	FBlendParameter BlendParameter = BlendSpace->GetBlendParameter((int)Axis);
	Min = BlendParameter.Min;
	Max = BlendParameter.Max;
}

TArray<UAnimInstance*> UExtendedAnimationLibrary::GetLinkedAnimLayers(const USkeletalMeshComponent* Target)
{
	TArray<UAnimInstance*> LinkedAnimLayers;
	if (Target)
	{
		UAnimInstance* AnimScriptInstance = Target->GetAnimInstance();
		if (AnimScriptInstance)
		{
			if (IAnimClassInterface* AnimBlueprintClass = IAnimClassInterface::GetFromClass(AnimScriptInstance->GetClass()))
			{
				for (const FStructProperty* LayerNodeProperty : AnimBlueprintClass->GetLinkedAnimLayerNodeProperties())
				{
					const FAnimNode_LinkedAnimLayer* Layer = LayerNodeProperty->ContainerPtrToValuePtr<FAnimNode_LinkedAnimLayer>(AnimScriptInstance);
					UAnimInstance* TargetInstance = Layer->GetTargetInstance<UAnimInstance>();
					if (TargetInstance)
					{
						LinkedAnimLayers.Add(TargetInstance);
					}
				}
			}
		}
	}
	return LinkedAnimLayers;
}

TArray<UAnimationAsset*> UExtendedAnimationLibrary::GetAllAnimations()
{
	TArray<UAnimationAsset*> Animations;
	
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	TArray<FAssetData> AnimationAssets;
	if (AssetRegistry.GetAssetsByClass(UAnimationAsset::StaticClass()->GetFName(), AnimationAssets, true))
	{
		for (const FAssetData& AssetData : AnimationAssets)
		{
			if (UAnimationAsset* Animation = Cast<UAnimationAsset>(AssetData.GetAsset()))
			{
				Animations.Add(Animation);
			}
		}
	}

	return Animations;
}

TArray<UAnimationAsset*> UExtendedAnimationLibrary::GetAllAnimationsForSkeleton(const USkeleton* Skeleton)
{
	TArray<UAnimationAsset*> Animations;

	if (IsValid(Skeleton))
	{
		TArray<UAnimationAsset*> AllAnimations = GetAllAnimations();
		for (UAnimationAsset* Animation : AllAnimations)
		{
			if (Animation->GetSkeleton() == Skeleton)
			{
				Animations.Add(Animation);
			}
		}
	}

	return Animations;
}
