// Copyright 2023 Dream Seed LLC.

#include "ExtendedUnrealLibrary.h"


#include "ExtendedUnrealModule.h"

#if WITH_EDITOR
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#endif

#include "UObject/NameTypes.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "GameFramework/Actor.h"



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

//void UExtendedUnrealLibrary::ExploreFolders()
//{
//	//TArray<FContentBrowserItem> SelectedFiles;
//	//TWeakPtr<SAssetView> AssetView;
//
//	//ContentBrowserUtils::ExploreFolders(SelectedFiles, AssetView.Pin().ToSharedRef());
//}

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

//void UExtendedUnrealLibrary::MakeBrushFromSVGPath(const FString SVGPath, FSlateBrush& Brush, const FVector2D& InImageSize)
//{
//	//Brush = new IMAGE_BRUSH_SVG(SVGPath, InImageSize);
//	//FSlateBrush aBrush = new IMAGE_BRUSH_SVG(SVGPath, InImageSize);
//	//FSlateVectorImageBrush aBrush = new IMAGE_BRUSH_SVG(SVGPath, InImageSize);
//	// 
//	//Cast<FSlateStyleSet>(FCoreStyle::Get()).GetContentRootDir();
//	//FSlateBrush aBrush = FSlateVectorImageBrush(RootToContentDir(SVGPath, TEXT(".svg")), InImageSize)
//
//	Brush = FSlateBrush();
//}

FName UExtendedUnrealLibrary::GetSoftClassName(const TSoftClassPtr<UObject>& Class)
{
	return Class->GetFName();
}

FText UExtendedUnrealLibrary::GetSoftClassDisplayNameText(const TSoftClassPtr<UObject>& Class)
{
#if WITH_EDITORONLY_DATA
	if (Class.IsValid())
	{
		return Class.Get()->GetDisplayNameText();
	}
	else
#endif //WITH_EDITORONLY_DATA
	{
		FString AssetName = Class.GetAssetName();
		return FText::FromString(AssetName);
	}

	//return Class.IsValid() ? Class.Get()->GetDisplayNameText() : FText::FromString(Class.GetAssetName());
}

FText UExtendedUnrealLibrary::GetClassDisplayNameText(const UClass* Class)
{
#if WITH_EDITORONLY_DATA
	return IsValid(Class) ? Class->GetDisplayNameText() : FText();
#else
	return FText();
#endif //WITH_EDITORONLY_DATA
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

UActorComponent* UExtendedUnrealLibrary::GetComponentByName(AActor* Target, TSubclassOf<UActorComponent> ComponentClass, FName ComponentName, bool bIncludeChildActors)
{
	if (IsValid(Target))
	{
		TArray<UActorComponent*> Components;
		Target->GetComponents(ComponentClass, Components, bIncludeChildActors);

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

//void UExtendedUnrealLibrary::SetConstraintMaxForce(UPhysicsConstraintComponent* PhysicsConstraintComponent, double MaxForceX, double MaxForceY, double MaxForceZ)
//{
//	//PhysicsConstraintComponent->ConstraintInstance.constraint;
//	//FPhysicsConstraintHandle& InConstraintRef;
//	//InConstraintRef.Constraint
//		//FConstraintProfileProperties
//		//LinearDrive.ZDrive.MaxForce
//}

TArray<AActor*> UExtendedUnrealLibrary::GetAttachedActorsOfClass(const AActor* Target, TSubclassOf<AActor> Class, bool bRecursivelyIncludeAttachedActors)
{
	TArray<AActor*> AttachedActors;
	GetAttachedActorsOfClass_InternalAppend(Target, Class, AttachedActors, bRecursivelyIncludeAttachedActors);
	return AttachedActors;
}

void UExtendedUnrealLibrary::GetAttachedActorsOfClass_InternalAppend(const AActor* Target, TSubclassOf<AActor> Class, TArray<AActor*>& AttachedActors, bool bRecursivelyIncludeAttachedActors)
{
	if (!Target) return;

	if (!Class) Class = AActor::StaticClass();

	Target->ForEachAttachedActors([Target, Class, bRecursivelyIncludeAttachedActors, &AttachedActors](AActor* AttachedActor)
		{
			if (AttachedActor->GetClass()->IsChildOf(Class))
			{
				int32 OriginalNumActors = AttachedActors.Num();

				if ((OriginalNumActors <= AttachedActors.AddUnique(AttachedActor)) && bRecursivelyIncludeAttachedActors)
				{
					GetAttachedActorsOfClass_InternalAppend(Target, Class, AttachedActors, true);
				}
			}
			return true;
		});
}

AActor* UExtendedUnrealLibrary::GetFirstAttachedActorOfClass(const AActor* Target, TSubclassOf<AActor> Class)
{
	if (!Target) return nullptr;

	if (!Class) Class = AActor::StaticClass();

	AActor* AttachedActor = nullptr;
	Target->ForEachAttachedActors([Target, Class, &AttachedActor](AActor* LoopAttachedActor)
		{
			if (LoopAttachedActor->GetClass()->IsChildOf(Class))
			{
				AttachedActor = LoopAttachedActor;
				return false;
			}
			return true;
		});

	return AttachedActor;
}