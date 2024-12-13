// Copyright 2023 Dream Seed LLC.

#pragma once



#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExtendedAnimationLibrary.generated.h"


/** Interpolation data types. */
UENUM(BlueprintType)
enum class EExtendedBlendSpaceAxis : uint8
{
	BSA_X = 0 UMETA(DisplayName = "Horizontal (X) Axis"),
	BSA_Y = 1 UMETA(DisplayName = "Vertical (Y) Axis"),
	BSA_Z = 2 UMETA(DisplayName = "Depth (Z) Axis", Hidden),
};


/**
 * 
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedAnimationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 * Get the min & max value for the given axis.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blend Space")
	static void GetBlendSpaceAxisMinMax(class UBlendSpace* BlendSpace, EExtendedBlendSpaceAxis Axis, double& Min, double& Max);

	/** Get all linked layer Animation Instances for the target SkeletalMeshComponent. */
	UFUNCTION(BlueprintCallable, Category = "Components|SkeletalMesh|Animation Blueprint Linking")
	static TArray<UAnimInstance*> GetLinkedAnimLayers(const class USkeletalMeshComponent* Target);

	/** Get all Animation Assets. */
	UFUNCTION(BlueprintCallable, Category = "Animation")
	static TArray<UAnimationAsset*> GetAllAnimations();

	/** Get all animation assets for the target Skeleton. */
	UFUNCTION(BlueprintCallable, Category = "Animation")
	static TArray<UAnimationAsset*> GetAllAnimationsForSkeleton(const USkeleton* Skeleton);
};
