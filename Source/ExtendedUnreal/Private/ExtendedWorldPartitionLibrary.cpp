// Copyright 2023 Dream Seed LLC.


#include "ExtendedWorldPartitionLibrary.h"

#include "WorldPartition/WorldPartitionSubsystem.h"
#include "WorldPartition/WorldPartitionRuntimeCell.h"
#include "Components/WorldPartitionStreamingSourceComponent.h"




bool UExtendedWorldPartitionLibrary::IsCollisionLoaded(const UObject* WorldContextObject, const FName TargetGrid, const FVector& Location)
{
	// This function is adapted from \Engine\Plugins\Runtime\MassGameplay\Source\MassRepresentation\Private\MassRepresentationSubsystem.cpp | IsCollisionLoaded

	if (!WorldContextObject)
	{
		return false;
	}

	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		return false;
	}

	UWorldPartitionSubsystem* WorldPartitionSubsystem = World->GetSubsystem<UWorldPartitionSubsystem>();
	if (!WorldPartitionSubsystem)
	{
		// Assuming that all collisions are loaded if not using WorldPartition.
		return true;
	}

	// @todo optimize by doing one query per cell
	// Build a query source
	TArray<FWorldPartitionStreamingQuerySource> QuerySources;
	FWorldPartitionStreamingQuerySource& QuerySource = QuerySources.Emplace_GetRef();
	QuerySource.bSpatialQuery = true;
	QuerySource.Location = Location;
	//QuerySource.Rotation = Transform.Rotator();
	if (!TargetGrid.IsNone())
	{
		QuerySource.TargetGrids.Add(TargetGrid);
	}
	QuerySource.bUseGridLoadingRange = false;
	QuerySource.Radius = 1.f; // 1cm should be enough to know if grid is loaded at specific area
	QuerySource.bDataLayersOnly = false;

	// Execute query
	return WorldPartitionSubsystem->IsStreamingCompleted(EWorldPartitionRuntimeCellState::Activated, QuerySources, /*bExactState*/ false);
}

void UExtendedWorldPartitionLibrary::SetWorldPartitionStreamingSource_DefaultVisualizerLoadingRange(UWorldPartitionStreamingSourceComponent* StreamingSourceComponent, const float Range)
{
#if WITH_EDITORONLY_DATA
	if (IsValid(StreamingSourceComponent))
	{
		StreamingSourceComponent->DefaultVisualizerLoadingRange = Range;
	}
#endif
}
