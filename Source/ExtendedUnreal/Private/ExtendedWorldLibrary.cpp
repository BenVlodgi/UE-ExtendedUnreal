// Copyright 2023 Dream Seed LLC.

#include "ExtendedWorldLibrary.h"


#include "ExtendedUnrealModule.h"
#include "CoreMinimal.h"



UExtendedWorldLibrary::UExtendedWorldLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UExtendedWorldLibrary::GetWorldGravity(const UObject* WorldContextObject)
{
	if (IsValid(WorldContextObject))
	{
		UWorld* World = WorldContextObject->GetWorld();

		if (IsValid(World))
		{
			return World->GetGravityZ();
		}
	}
	
	return 0;
}

WorldType UExtendedWorldLibrary::GetWorldType(UObject* WorldContextObject)
{
	return IsValid(WorldContextObject) ? 
		WorldTypeToBlueprintCompatible(WorldContextObject->GetWorld()->WorldType) : 
		WorldType::None;
}

WorldType UExtendedWorldLibrary::WorldTypeToBlueprintCompatible(EWorldType::Type WorldType)
{
	switch (WorldType)
	{
		case EWorldType::None:			return WorldType::None;
		case EWorldType::Game:			return WorldType::Game;
		case EWorldType::Editor:		return WorldType::Editor;
		case EWorldType::PIE:			return WorldType::PIE;
		case EWorldType::EditorPreview: return WorldType::EditorPreview;
		case EWorldType::GamePreview:	return WorldType::GamePreview;
		case EWorldType::GameRPC:		return WorldType::GameRPC;
		case EWorldType::Inactive:		return WorldType::Inactive;
	}

	return WorldType::None;
}

bool UExtendedWorldLibrary::IsGameWorld(UObject* WorldContextObject)
{
	return IsValid(WorldContextObject) ?
		WorldContextObject->GetWorld()->IsGameWorld() :
		false;
}

bool UExtendedWorldLibrary::IsEditorWorld(UObject* WorldContextObject)
{
	return IsValid(WorldContextObject) ?
		WorldContextObject->GetWorld()->IsEditorWorld() :
		false;
}

bool UExtendedWorldLibrary::IsPreviewWorld(UObject* WorldContextObject)
{
	return IsValid(WorldContextObject) ?
		WorldContextObject->GetWorld()->IsPreviewWorld() :
		false;
}

bool UExtendedWorldLibrary::IsPlayingOrSimulatingInEditor(UObject* WorldContextObject)
{
	return IsValid(WorldContextObject) ?
		WorldContextObject->GetWorld()->IsPlayInEditor() :
		false;
}

bool UExtendedWorldLibrary::IsPlayingInEditor(UObject* WorldContextObject)
{
	return IsValid(WorldContextObject) ?
		WorldContextObject->GetWorld()->IsPlayInEditor()
#if WITH_EDITOR
		&& !GEditor->IsSimulateInEditorInProgress()
#endif
		: false;
}

bool UExtendedWorldLibrary::IsSimulatingInEditor(UObject* WorldContextObject)
{
	return IsValid(WorldContextObject) ?
		WorldContextObject->GetWorld()->IsPlayInEditor()
#if WITH_EDITOR
		&& GEditor->IsSimulateInEditorInProgress()
#endif
		: false;
}

void UExtendedWorldLibrary::WorldTypeQuery(UObject* WorldContextObject, const bool bGame, const bool bPIE, const bool bEditor, const bool bEditorPreview, const bool bGamePreview, const bool bGameRPC, const bool bInactiveEditor, bool& bMatch)
{
	bMatch = false;
	switch(UExtendedWorldLibrary::GetWorldType(WorldContextObject))
	{
		case WorldType::None:			bMatch = false; break;
		case WorldType::Game:			bMatch = bGame; break;
		case WorldType::PIE:			bMatch = bPIE; break;
		case WorldType::Editor:			bMatch = bEditor; break;
		case WorldType::EditorPreview:	bMatch = bEditorPreview; break;
		case WorldType::GamePreview:	bMatch = bGamePreview; break;
		case WorldType::GameRPC:		bMatch = bGameRPC; break;
		case WorldType::Inactive:		bMatch = bInactiveEditor; break;
		default:						bMatch = false; break;
	}
}
