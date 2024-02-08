// Copyright 2023 Dream Seed LLC.

#include "ExtendedUnrealLibrary.h"


#include "ExtendedUnrealModule.h"
#include "Structs/DelegateHandleWrapper.h"

#if WITH_EDITOR
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#endif

#include "UObject/NameTypes.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Styling/SlateIconFinder.h"
#include "Components/TimelineComponent.h"

#include "Components/SplineComponent.h"


UExtendedUnrealLibrary::UExtendedUnrealLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

//void UExtendedUnrealLibrary::ExploreFolders()
//{
//	//TArray<FContentBrowserItem> SelectedFiles;
//	//TWeakPtr<SAssetView> AssetView;
//
//	//ContentBrowserUtils::ExploreFolders(SelectedFiles, AssetView.Pin().ToSharedRef());
//}

FSlateBrush UExtendedUnrealLibrary::MakeBrushFromAppStyle(const FName Name)
{
	const FSlateBrush* localBrush = FAppStyle::Get().GetBrush(Name);
	return localBrush ? *localBrush : FSlateBrush();
	
}

FSlateBrush UExtendedUnrealLibrary::MakeBrushFromStyleSet(const FName StyleSetName, const FName Name)
{
	return *FSlateIcon(StyleSetName, Name).GetIcon();
}

FSlateBrush UExtendedUnrealLibrary::MakeBrushFromSlateIcon(const FName Name)
{
	return *FSlateIconFinder::FindIcon(Name).GetIcon();
}

//FSlateBrush UExtendedUnrealLibrary::MakeBrushFromSVGPath(const FString SVGPath, const FVector2D& InImageSize)
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

UActorComponent* UExtendedUnrealLibrary::GetBaseComponentReferenceComponent(UPARAM(ref) const FBaseComponentReference& Target, AActor* FallbackActor)
{
	return Target.ExtractComponent(FallbackActor);
}

UActorComponent* UExtendedUnrealLibrary::GetComponentReferenceComponent(UPARAM(ref) const FComponentReference& Target, AActor* FallbackActor)
{
	return Target.GetComponent(FallbackActor);
}

UActorComponent* UExtendedUnrealLibrary::GetSoftComponentReferenceComponent(UPARAM(ref) const FSoftComponentReference& Target, AActor* FallbackActor)
{
	return Target.GetComponent(FallbackActor);
}

FComponentReference UExtendedUnrealLibrary::MakeComponentReference(const UActorComponent* Component)
{
	// See FComponentEditorUtils::MakeComponentReference

	FComponentReference Result;
	if (Component)
	{
		AActor* ComponentOwner = Component->GetOwner();
		if (ComponentOwner)
		{
			Result.OtherActor = ComponentOwner;
		}

		// TODO: Check how this behaves when ComponentOwner == nullptr
		Result.PathToComponent = Component->GetPathName(ComponentOwner);
	}

	return Result;
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

void UExtendedUnrealLibrary::ComponentSetActiveSafe(UActorComponent* Component, bool bNewActive)
{
	if (IsValid(Component))
	{
		if (Component->IsOwnerRunningUserConstructionScript())
		{
			Component->SetAutoActivate(bNewActive);
		}
		else
		{
			Component->SetActive(bNewActive);
		}
	}
}

bool UExtendedUnrealLibrary::ActorIsRunningConstruction(const AActor* Actor)
{
	return IsValid(Actor) ?
		Actor->IsRunningUserConstructionScript() :
		false;
}
void UExtendedUnrealLibrary::ActorIsBeginningPlay(const AActor* Actor, bool& BeginningPlay, bool& BeginningPlayFromLevelStreaming)
{
	if (IsValid(Actor))
	{
		BeginningPlay = Actor->IsActorBeginningPlay();
		BeginningPlayFromLevelStreaming = Actor->IsActorBeginningPlayFromLevelStreaming();
	}
	else
	{
		BeginningPlay = false;
		BeginningPlayFromLevelStreaming = false;
	}
}

bool UExtendedUnrealLibrary::ActorHasBegunPlay(const AActor* Actor)
{
	return IsValid(Actor) ?
		Actor->HasActorBegunPlay() :
		false;
}

bool UExtendedUnrealLibrary::ActorIsInPlay(const AActor* Actor)
{
	return IsValid(Actor) ?
		Actor->HasActorBegunPlay() || Actor->IsActorBeginningPlay() :
		false;
}


//bool UExtendedUnrealLibrary::IsDuringConstructor()
//{
//	return FUObjectThreadContext::Get().IsInConstructor > 0;
//}

void UExtendedUnrealLibrary::SetActorDisplayName(AActor* Actor, FString DisplayName)
{
#if WITH_EDITOR
	if (IsValid(Actor))
	{
		Actor->SetActorLabel(*DisplayName);
	}

#endif //WITH_EDITOR
}

TArray<float> UExtendedUnrealLibrary::GetCustomPrimitiveData(const UPrimitiveComponent* Target)
{
	if (IsValid(Target))
	{
		const FCustomPrimitiveData& PrimitiveData = Target->GetCustomPrimitiveData();
		return PrimitiveData.Data;
	}

	return TArray<float>();
}

float UExtendedUnrealLibrary::GetCustomPrimitiveDataFloat(const UPrimitiveComponent* Target, int32 DataIndex)
{
	if (IsValid(Target))
	{
		const FCustomPrimitiveData& PrimitiveData = Target->GetCustomPrimitiveData();
		if (PrimitiveData.Data.IsValidIndex(DataIndex))
		{
			return PrimitiveData.Data[DataIndex];
		}
	}

	return 0.0;
}

bool UExtendedUnrealLibrary::DoesClassImplementInterface(const UClass* Class, const TSubclassOf<UInterface> Interface)
{
	if (Interface != NULL && Class != NULL)
	{
		checkf(Interface->IsChildOf(UInterface::StaticClass()), TEXT("Interface parameter %s is not actually an interface."), *Interface->GetName());
		return Class->ImplementsInterface(Interface);
	}

	return false;
}


void UExtendedUnrealLibrary::DestroyAudioComponentWhenComplete(UAudioComponent* AudioComponent)
{
	if (!IsValid(AudioComponent))
	{
		if (AudioComponent->IsPlaying())
		{
			AudioComponent->DestroyComponent();
		}
		else
		{
			AudioComponent->bAutoDestroy = true;
		}
	}
}

bool UExtendedUnrealLibrary::IsActorInActorOwnerChain(const AActor* Target, const AActor* Actor)
{
	if (!IsValid(Target) || !IsValid(Actor))
	{
		return false;
	}

	TSet<const AActor*> CheckedOwners;
	for(const AActor* Owner = Target; IsValid(Owner); Owner = Target->GetOwner())
	{
		// If we've looped around, then the actor is not in the chain.
		if (CheckedOwners.Contains(Owner))
		{
			return false; 
		}

		// We found the owner!
		if (Owner == Actor)
		{
			return true;
		}

		CheckedOwners.Add(Owner);
	}

	// for-loop ends when it hits an invalid owner. Hence, the owner was not found.
	return false; 
}

bool UExtendedUnrealLibrary::IsActorInComponentOwnerChain(const UActorComponent* Target, const AActor* Actor)
{
	if (!IsValid(Target) || !IsValid(Actor))
	{
		return false;
	}

	return IsActorInActorOwnerChain(Target->GetOwner(), Actor);
}

TArray<AActor*> UExtendedUnrealLibrary::GetActorOwnerChain(const AActor* Target)
{
	TArray<AActor*> Owners;
	for (const AActor* Owner = Target; IsValid(Owner); Owner = Target->GetOwner())
	{
		if (Owners.Contains(Owner))
		{
			// If we've looped around, then get out of the loop.
			break;
		}

		Owners.Add((AActor*)Owner);
	}

	return Owners;
}

TArray<AActor*> UExtendedUnrealLibrary::GetComponentOwnerChain(const UActorComponent* Target)
{
	if (!IsValid(Target))
	{
		return TArray<AActor*>();
	}

	return GetActorOwnerChain(Target->GetOwner());
}

AActor* UExtendedUnrealLibrary::GetActorOwnerSafe(const AActor* Target)
{
	return IsValid(Target) ? Target->GetOwner() : nullptr;
}

AActor* UExtendedUnrealLibrary::GetComponentOwnerSafe(const UActorComponent* Target)
{
	return IsValid(Target) ? Target->GetOwner() : nullptr;
}

bool UExtendedUnrealLibrary::IsNetStartupActor(const AActor* Target)
{
	return IsValid(Target) ? Target->IsNetStartupActor() : false;
}

const AActor* UExtendedUnrealLibrary::AsActorOrOwner(const UObject* Target)
{
	const AActor* Actor = Cast<AActor>(Target);
	if (IsValid(Actor))
	{
		return Actor;
	}

	const UActorComponent* Component = Cast<UActorComponent>(Target);
	if (IsValid(Component))
	{
		return Component->GetOwner();
	}

	return nullptr;
}

FDelegateHandleWrapper UExtendedUnrealLibrary::BindEventToOnTransformUpdated(USceneComponent* Target, FTransformUpdatedDelegate OnTransformUpdated)
{
	if (!IsValid(Target))
	{
		return FDelegateHandleWrapper();
	}

	FDelegateHandleWrapper Handle;
	Handle.DelegateHandle = Target->TransformUpdated.AddLambda(
		[OnTransformUpdated](USceneComponent* UpdatedComponent, EUpdateTransformFlags /*UpdateTransformFlags*/, ETeleportType /*TeleportType*/)
		{
			OnTransformUpdated.ExecuteIfBound(UpdatedComponent, UpdatedComponent->GetComponentToWorld());
		}
	);

	return Handle;
}

void UExtendedUnrealLibrary::UnbindEventFromOnTransformUpdated(USceneComponent* Target, const FDelegateHandleWrapper& Handle)
{
	if (!IsValid(Target))
	{
		return;
	}

	Target->TransformUpdated.Remove(Handle.DelegateHandle);
}

void UExtendedUnrealLibrary::SetPreviewSkeletalMesh(UAnimationAsset* AnimationAsset, USkeletalMesh* PreviewMesh)
{
	if (IsValid(AnimationAsset))
	{
		AnimationAsset->SetPreviewMesh(PreviewMesh);
	}
}

double UExtendedUnrealLibrary::GetDistanceAlongSplineAtTime(const class USplineComponent* Target, double Time, bool bUseConstantVelocity)
{
	if (!Target)
	{
		return 0;
	}

	if (Target->Duration == 0.0f)
	{
		return 0;
	}

	if (bUseConstantVelocity)
	{
		const double Distance = Time / Target->Duration * Target->GetSplineLength();

		// Evaluate distance along spline.
		return Target->SplineCurves.ReparamTable.Eval(Distance, 0.0f);
	}
	else
	{
		const int32 NumPoints = Target->SplineCurves.Position.Points.Num();
		const int32 NumSegments = Target->IsClosedLoop() ? NumPoints : NumPoints - 1;
		const float TimeMultiplier = NumSegments / Target->Duration;
		const double Distance = Time * TimeMultiplier;

		// Evaluate distance along spline.
		return Target->SplineCurves.ReparamTable.Eval(Distance, 0.0f);
	}
}

double UExtendedUnrealLibrary::GetTimeAlongSplineAtTime(const USplineComponent* Target, double Time, bool bUseConstantVelocity)
{
	if (!Target)
	{
		return 0;
	}
	const double Distance = GetDistanceAlongSplineAtTime(Target, Time, bUseConstantVelocity);

	if (bUseConstantVelocity)
	{
		return Distance / Target->GetNumberOfSplineSegments();
	}
	else
	{
		return Distance / GetDistanceAlongSplineAtTime(Target, 1.0, bUseConstantVelocity);
	}
}

double UExtendedUnrealLibrary::GetTimeAlongSplineAtSplinePoint(const USplineComponent* Target, int Index, bool bUseConstantVelocity)
{
	if (!Target)
	{
		return 0;
	}

	const int32 NumPoints = Target->GetNumberOfSplinePoints();
	const int32 NumSegments = Target->IsClosedLoop() ? NumPoints : NumPoints - 1;
	if (NumSegments == 0)
	{
		return 0;
	}

	// Linear Time.
	const double Time = (double)Index / (double)NumSegments;
	const double Distance = GetDistanceAlongSplineAtTime(Target, Time, bUseConstantVelocity);

	if (bUseConstantVelocity)
	{
		return Distance / Target->GetNumberOfSplineSegments();
	}
	else
	{
		return Distance / GetDistanceAlongSplineAtTime(Target, 1.0, bUseConstantVelocity);
	}
}

void UExtendedUnrealLibrary::GetInterfaceImplementor(AActor* Actor, TSubclassOf<UInterface> Interface, const bool bPreferComponent, UObject*& Implementor)
{
	Implementor = nullptr;

	if (!IsValid(Actor) || !IsValid(Interface))
	{
		return;
	}

	
	if (!bPreferComponent)
	{
		// Check Actor
		if (Actor->GetClass()->ImplementsInterface(Interface))
		{
			Implementor = Actor;
			return;
		}
	}

	// Check Component
	Implementor = Actor->FindComponentByInterface(Interface);
	if (IsValid(Implementor))
	{
		return;
	}

	if (bPreferComponent)
	{
		// Check Actor
		if (Actor->GetClass()->ImplementsInterface(Interface))
		{
			Implementor = Actor;
			return;
		}
	}
}

TArray<UObject*> UExtendedUnrealLibrary::GetInterfaceImplementors(AActor* Actor, TSubclassOf<UInterface> Interface)
{
	TArray<UObject*> Implementors;

	if (!IsValid(Actor) || !IsValid(Interface))
	{
		return Implementors;
	}

	// Check Actor
	if (Actor->GetClass()->ImplementsInterface(Interface))
	{
		Implementors.Add(Actor);
	}

	// Check Components
	TArray<UActorComponent*> Components = Actor->GetComponentsByInterface(Interface);
	for (auto* Component : Components)
	{
		Implementors.Add(Component);
	}

	return Implementors;
}


bool UExtendedUnrealLibrary::GetPlayerViewportTransform(const APlayerController* Player, FTransform& Transform)
{
	const ULocalPlayer* LP = Player ? Player->GetLocalPlayer() : nullptr;
	if (LP && LP->ViewportClient)
	{
		FSceneViewProjectionData ProjectionData;
		if (LP->GetProjectionData(LP->ViewportClient->Viewport, /*out*/ ProjectionData))
		{
			Transform = FTransform(ProjectionData.ViewRotationMatrix.ToQuat(), ProjectionData.ViewOrigin);
			return true;
		}
	}

	Transform = FTransform::Identity;
	return false;
}


void UExtendedUnrealLibrary::SetTimelineDuration(UTimelineComponent* Timeline, double )
{
	if (IsValid(Timeline))
	{
		Timeline->SetPlayRate(Timeline->GetTimelineLength() / FMath::Max(0.001, Duration));
	}
}