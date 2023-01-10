// Copyright 2022 Dream Seed LLC.

#include "ExtendedUnrealLibrary.h"
#include "ExtendedUnrealModule.h"


#if WITH_EDITOR
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#endif

#include <Editor/ContentBrowser/Private/ContentBrowserUtils.h>
#include "UObject/NameTypes.h"
#include "CoreMinimal.h"

UExtendedUnrealLibrary::UExtendedUnrealLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UExtendedUnrealLibrary::GetWorldGravity(const UObject* WorldContextObject)
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



void UExtendedUnrealLibrary::ExploreFolders()
{
	//TArray<FContentBrowserItem> SelectedFiles;
	//TWeakPtr<SAssetView> AssetView;

	//ContentBrowserUtils::ExploreFolders(SelectedFiles, AssetView.Pin().ToSharedRef());
}


WorldType UExtendedUnrealLibrary::GetWorldType(UObject* WorldContextObject)
{
	return IsValid(WorldContextObject) ? 
		WorldTypeToBlueprintCompatible(WorldContextObject->GetWorld()->WorldType) : 
		WorldType::None;
}

WorldType UExtendedUnrealLibrary::WorldTypeToBlueprintCompatible(EWorldType::Type WorldType)
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

void UExtendedUnrealLibrary::MakeBrushFromAppStyle(FName Name, FSlateBrush& Brush)
{
	const FSlateBrush* localBrush = FAppStyle::Get().GetBrush(Name);
	Brush = localBrush ? *localBrush : FSlateBrush();
}


void UExtendedUnrealLibrary::MakeBrushFromSVGPath(const FString SVGPath, FSlateBrush& Brush, const FVector2D& InImageSize)
{
	//Brush = new IMAGE_BRUSH_SVG(SVGPath, InImageSize);
	//FSlateBrush aBrush = new IMAGE_BRUSH_SVG(SVGPath, InImageSize);
	//FSlateVectorImageBrush aBrush = new IMAGE_BRUSH_SVG(SVGPath, InImageSize);
	// 
	//Cast<FSlateStyleSet>(FCoreStyle::Get()).GetContentRootDir();
	//FSlateBrush aBrush = FSlateVectorImageBrush(RootToContentDir(SVGPath, TEXT(".svg")), InImageSize)

	Brush = FSlateBrush();
}

FName UExtendedUnrealLibrary::GetSoftClassName(const TSoftClassPtr<UObject>& Class)
{
	return Class->GetFName();
}


FText UExtendedUnrealLibrary::GetSoftClassDisplayNameText(const TSoftClassPtr<UObject>& Class)
{
	if (Class.IsValid())
	{
		return Class.Get()->GetDisplayNameText();
	}
	else
	{
		FString AssetName = Class.GetAssetName();
		return FText::FromString(AssetName);
	}

	//return Class.IsValid() ? Class.Get()->GetDisplayNameText() : FText::FromString(Class.GetAssetName());
}

FText UExtendedUnrealLibrary::GetClassDisplayNameText(const UClass* Class)
{
	return IsValid(Class) ? Class->GetDisplayNameText() : FText();
}

FName UExtendedUnrealLibrary::GetSoftObjectName(const TSoftObjectPtr<UObject>& Object)
{
	if (Object.IsValid())
	{
		return Object->GetFName();
	}
	else
	{
		FString AssetName = Object.GetAssetName();
		return FName(AssetName);
	}

	//return Object.IsValid() ? Object.Get()->GetFName() : FName(Object.GetAssetName());
}

UActorComponent* UExtendedUnrealLibrary::GetComponentReferenceComponent(UPARAM(ref)const FComponentReference& Target, AActor* FallbackActor)
{
	return Target.GetComponent(FallbackActor);
}

UActorComponent* UExtendedUnrealLibrary::GetComponentByName(AActor* Target, TSubclassOf<UActorComponent> ComponentClass, FName ComponentName)
{
	if (IsValid(Target))
	{
		TArray<UActorComponent*> Components;
		Target->GetComponents(ComponentClass, Components);

		for (UActorComponent* Component : Components)
		{
			if (Component && Component->GetFName() == ComponentName)
			{
				return Component;
			}
		}
	}

	return nullptr;
}

FString UExtendedUnrealLibrary::Conv_GameplayTagToString(const FGameplayTag& GameplayTag)
{
	return GameplayTag.ToString();
}

FName UExtendedUnrealLibrary::Conv_GameplayTagToName(const FGameplayTag& GameplayTag)
{
	return GameplayTag.GetTagName();
}

void UExtendedUnrealLibrary::ToDisplayString(const FString String, FString& DisplayString, const bool bIsBool)
{
	DisplayString = *FName::NameToDisplayString(String, bIsBool);
}

void UExtendedUnrealLibrary::FocusViewportToSelection(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (GUnrealEd && WorldContextObject)
	{
		GUnrealEd->Exec(WorldContextObject->GetWorld(), TEXT("CAMERA ALIGN ACTIVEVIEWPORTONLY"));
	}
#endif
}

//void UExtendedUnrealLibrary::FocusViewportToActor(const UObject* WorldContextObject)
//{
//#if WITH_EDITOR
//	// TODO: Implement this
//#endif
//}


TArray<UObject*> UExtendedUnrealLibrary::CastArray(const TArray<UObject*> Array, const TSubclassOf<UObject> Class)
{
	return Array;
}
