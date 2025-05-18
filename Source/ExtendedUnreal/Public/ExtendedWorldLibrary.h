// Copyright 2023 Dream Seed LLC.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Enums/WorldType.h"


#include "ExtendedWorldLibrary.generated.h"

UENUM()
enum class EMatchOther : uint8
{
	Match,
	Other
};

/**
 * Functions relating to the background world.
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedWorldLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * Returns the Z component of the current world gravity.
	 *
	 * @return Z component of current world gravity.
	 */
	UFUNCTION(BlueprintPure, Category = "World", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static float GetWorldGravity(const UObject* WorldContextObject);

	/** True when world is in the process of running the construction script for an actor */
	UFUNCTION(BlueprintPure, Category = "World", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext, ReturnDisplayName = "RunningConstruction"))
	static bool IsRunningConstructionScript(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static WorldType GetWorldType(UObject* WorldContextObject);

	static WorldType WorldTypeToBlueprintCompatible(EWorldType::Type WorldType);

	/** Returns true if the world type is: PIE, Game, GamePreview, or GameRPC. */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static bool IsGameWorld(UObject* WorldContextObject);

	/** Returns true if the world type is: PIE, Editor, or EditorPreview. */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static bool IsEditorWorld(UObject* WorldContextObject);

	/** Returns true if the world type is: EditorPreview, or GamePreview. */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext))
	static bool IsPreviewWorld(UObject* WorldContextObject);


	/** Returns true if the WorldType is: PIE. */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext, DevelopmentOnly, keywords = "PIE,SIE"))
	static bool IsPlayingOrSimulatingInEditor(UObject* WorldContextObject);

	/**
	 * Returns true if the WorldType is: PIE and PlaySessionWorldType is PlayInEditor.
	 * Note: Returns false if Simulating in Editor.
	 */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext, DevelopmentOnly, keywords = "PIE"))
	static bool IsPlayingInEditor(UObject* WorldContextObject);

	/** Returns true if the WorldType is: PIE and PlaySessionWorldType is SimulateInEditor. */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext, DevelopmentOnly, keywords = "SIE"))
	static bool IsSimulatingInEditor(UObject* WorldContextObject);


	/**
	 * Passes if the world type is the same as one of the input filters.
	 * @param bGame - When this code is run in game world.
	 * @param bPIE - When this code is run in a Play In Editor (PIE) Game world.
	 * @param bEditor - When this code is run for an editor window (i.e. level editor).
	 * @param bEditorPreview - When this code is run for a preview tool (i.e. actor viewport).
	 * @param bGamePreview - When this code is run in a preview world for a game.
	 * @param bGameRPC - When this code is run a minimal RPC world for a game.
	 * @param bInactiveEditor - When this code is run in an editor world that was loaded but not currently being edited in the level editor.
	 */
	UFUNCTION(BlueprintPure, Category = "World|Type", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", CallableWithoutWorldContext, AdvancedDisplay = "bGamePreview,bGameRPC,bInactiveEditor"))
	static void WorldTypeQuery(UObject* WorldContextObject, const bool bGame, const bool bPIE, const bool bEditor, const bool bEditorPreview, const bool bGamePreview, const bool bGameRPC, const bool bInactiveEditor, bool& bMatch);

};
