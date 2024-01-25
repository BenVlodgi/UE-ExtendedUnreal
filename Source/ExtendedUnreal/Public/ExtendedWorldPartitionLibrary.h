// Copyright 2023 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"


#include "ExtendedWorldPartitionLibrary.generated.h"


/**
 * Helper functions for World Partition.
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedWorldPartitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "World Partition", meta = (WorldContext = "WorldContextObject"))
	static bool IsCollisionLoaded(const UObject* WorldContextObject, const FName TargetGrid, const FVector& Location);

	UFUNCTION(BlueprintCallable, Category = "Streaming|Debug", meta = (CallableWithoutWorldContext, DevelopmentOnly, DisplayName = "Set Default Visualizer Loading Range", CompactNodeTitle = "VisualizerRange"))
	static void SetWorldPartitionStreamingSource_DefaultVisualizerLoadingRange(class UWorldPartitionStreamingSourceComponent* StreamingSourceComponent, const float Range);
};
