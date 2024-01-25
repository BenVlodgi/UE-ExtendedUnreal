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
