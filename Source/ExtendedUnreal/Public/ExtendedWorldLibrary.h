// Copyright 2023 Dream Seed LLC.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Enums/WorldType.h"


#include "ExtendedWorldLibrary.generated.h"

/**
 * Functions relating to the background world.
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedWorldLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "World", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static float GetWorldGravity(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static WorldType GetWorldType(UObject* WorldContextObject);

	static WorldType WorldTypeToBlueprintCompatible(EWorldType::Type WorldType);

	//* Returns true if the world type is: PIE, Game, GamePreview, or GameRPC. */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static bool IsGameWorld(UObject* WorldContextObject);

	//* Returns true if the world type is: PIE, Editor, or EditorPreview. */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static bool IsEditorWorld(UObject* WorldContextObject);

	//* Returns true if the world type is: EditorPreview, or GamePreview. */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static bool IsPreviewWorld(UObject* WorldContextObject);

};
