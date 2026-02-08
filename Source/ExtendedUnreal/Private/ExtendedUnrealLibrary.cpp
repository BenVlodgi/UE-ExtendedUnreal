// Copyright 2025 Dream Seed LLC.

#include "ExtendedUnrealLibrary.h"


#include "ExtendedUnrealModule.h"
#include "ExtendedUnrealLog.h"
#include "ExtendedMathLibrary.h"
#include "Structs/DelegateHandleWrapper.h"
#include "Structs/VectorArray.h"

#if WITH_EDITOR
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#include "LevelEditorViewport.h"
#include "LevelEditor.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#endif

#include "UObject/NameTypes.h"
#include "UObject/ICookInfo.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicsEngine/BodySetup.h"
#include "PhysicsEngine/ConvexElem.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Styling/SlateIconFinder.h"
#include "Components/AudioComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DelayAction.h"
#include "DrawDebugHelpers.h"
#include "ClearQuad.h"
#include "CollisionQueryParams.h"
#include "RHIContext.h"
#include "RHIUtilities.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/OverlapResult.h"
#include "EngineUtils.h"
#include "ShaderCompiler.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialExpressionStaticSwitchParameter.h"



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

bool UExtendedUnrealLibrary::ComponentGetActiveSafe(const UActorComponent* Component)
{
	return !IsValid(Component) ? false
		: Component->IsOwnerRunningUserConstructionScript() ? Component->bAutoActivate
		: Component->IsActive();
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

void UExtendedUnrealLibrary::SetActorDisplayName(AActor* Actor, const FString DisplayName)
{
#if WITH_EDITOR
	if (IsValid(Actor))
	{
		Actor->SetActorLabel(*DisplayName);
	}

#endif //WITH_EDITOR
}

void UExtendedUnrealLibrary::RenameObject(UObject* Object, const FString Name)
{
	if (IsValid(Object))
	{
		const FString CleanNewName = MakeUniqueObjectName(Object->GetOuter(), Object->GetClass(), FName(Name)).ToString();
		if (Object->Rename(*CleanNewName, nullptr, REN_Test))
		{
			Object->Rename(*CleanNewName, nullptr, REN_DoNotDirty | REN_ForceNoResetLoaders);
		}
	}
}

bool UExtendedUnrealLibrary::SetRootComponent(AActor* Actor, USceneComponent* NewRootComponent)
{
	/** Only components owned by this actor can be used as a its root component. */
	
	if (IsValid(Actor))
	{
		return Actor->SetRootComponent(NewRootComponent);
	}
	return false;
}

AActor* UExtendedUnrealLibrary::SpawnActorFromClass(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, ESpawnActorScaleMethod TransformScaleMethod, AActor* Owner, APawn* Instigator)
{
	AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(WorldContextObject, ActorClass, SpawnTransform, CollisionHandlingOverride, Owner, TransformScaleMethod);
	
	if (Actor)
	{
		if (Instigator)
		{
			Actor->SetInstigator(Instigator);
		}

		// TODO: Set Parameters before construct.

		UGameplayStatics::FinishSpawningActor(Actor, SpawnTransform, TransformScaleMethod);
	}

	return Actor;
}

int32 UExtendedUnrealLibrary::ExtendedHashCombine(const int32 A, const int32 B, const bool bOrderDependent)
{
	if (bOrderDependent)
	{
		return HashCombine(A, B);
	}

	if (A < B)
	{
		return HashCombine(A, B);
	}
	else
	{
		return HashCombine(B, A);
	}
}

int32 UExtendedUnrealLibrary::ExtendedHashCombineFast(int32 A, int32 B, const bool bOrderDependent)
{
	if (bOrderDependent)
	{
		return HashCombineFast(A, B);
	}

	if (A < B)
	{
		return HashCombineFast(A, B);
	}
	else
	{
		return HashCombineFast(B, A);
	}
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

FDelegateHandleWrapper UExtendedUnrealLibrary::BindEventToOnTransformUpdated(USceneComponent* Target, FTransformUpdatedDelegate OnTransformUpdated, bool bLocationChange, bool bRotationChange, bool bScaleChange, double Tolerance)
{
	FDelegateHandleWrapper Handle;

	if (!IsValid(Target))
	{
		return Handle;
	}

	// Shared pointer holds persistent last location for the lambda.
	TSharedPtr<FTransform> LastTransform = MakeShared<FTransform>(Target->GetComponentToWorld());

	if (bLocationChange && bRotationChange && bScaleChange)
	{
		Handle.DelegateHandle = Target->TransformUpdated.AddLambda(
			[OnTransformUpdated, LastTransform, Tolerance](USceneComponent* UpdatedComponent, EUpdateTransformFlags /*UpdateTransformFlags*/, ETeleportType /*TeleportType*/)
			{
				const FTransform& NewTransform = UpdatedComponent->GetComponentToWorld();
				if (!NewTransform.Equals(*LastTransform), Tolerance)
				{
					const FTransform OldTransform = *LastTransform;
					*LastTransform = NewTransform;
					OnTransformUpdated.ExecuteIfBound(UpdatedComponent, OldTransform, NewTransform);
				}
			}
		);
	}
	else if(bLocationChange || bRotationChange || bScaleChange)
	{
		// Some mix of change notifies.
		Handle.DelegateHandle = Target->TransformUpdated.AddLambda(
			[OnTransformUpdated, LastTransform, bLocationChange, bRotationChange, bScaleChange, Tolerance](USceneComponent* UpdatedComponent, EUpdateTransformFlags /*UpdateTransformFlags*/, ETeleportType /*TeleportType*/)
			{
				const FTransform& NewTransform = UpdatedComponent->GetComponentToWorld();
				if ((bLocationChange && !NewTransform.GetLocation().Equals(LastTransform->GetLocation(), Tolerance)) ||
					(bRotationChange && !NewTransform.GetRotation().Equals(LastTransform->GetRotation(), Tolerance)) ||
					(bScaleChange && !NewTransform.GetScale3D().Equals(LastTransform->GetScale3D(), Tolerance)))
				{
					const FTransform OldTransform = *LastTransform;
					*LastTransform = NewTransform;
					OnTransformUpdated.ExecuteIfBound(UpdatedComponent, OldTransform, NewTransform);
				}
			}
		);
	}
	else
	{
		// no notify requested.
	}

	return Handle;
}

FDelegateHandleWrapper UExtendedUnrealLibrary::BindEventToOnLocationChanged(USceneComponent* Target, FLocationUpdatedDelegate OnLocationChanged)
{
	if (!IsValid(Target))
	{
		return FDelegateHandleWrapper();
	}

	// Shared pointer holds persistent last location for the lambda.
	TSharedPtr<FVector> LastLocation = MakeShared<FVector>(Target->GetComponentLocation());

	FDelegateHandleWrapper Handle;
	Handle.DelegateHandle = Target->TransformUpdated.AddLambda(
		[OnLocationChanged, LastLocation](USceneComponent* UpdatedComponent, EUpdateTransformFlags /*UpdateTransformFlags*/, ETeleportType /*TeleportType*/)
		{
			const FVector& NewLocation = UpdatedComponent->GetComponentLocation();
			if (!NewLocation.Equals(*LastLocation))
			{
				FVector OldLocation = *LastLocation;
				*LastLocation = NewLocation;
				OnLocationChanged.ExecuteIfBound(UpdatedComponent, OldLocation, NewLocation);
			}
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

void UExtendedUnrealLibrary::UnbindEventFromOnLocationUpdated(USceneComponent* Target, const FDelegateHandleWrapper& Handle)
{
	if (!IsValid(Target))
	{
		return;
	}

	Target->TransformUpdated.Remove(Handle.DelegateHandle);
}

bool UExtendedUnrealLibrary::IsValid_DelegateHandleWrapper(UPARAM(Ref)FDelegateHandleWrapper& Handle)
{
	return Handle.IsValid();
}

void UExtendedUnrealLibrary::Reset_DelegateHandleWrapper(UPARAM(Ref)FDelegateHandleWrapper& Handle)
{
	Handle.Reset();
}

bool UExtendedUnrealLibrary::EqualEqual_DelegateHandleWrapper(FDelegateHandleWrapper A, FDelegateHandleWrapper B)
{
	return A == B;
}

bool UExtendedUnrealLibrary::NotEqual_DelegateHandleWrapper(FDelegateHandleWrapper A, FDelegateHandleWrapper B)
{
	return A != B;
}

void UExtendedUnrealLibrary::SetAutoPossessAI(APawn* Pawn, EAutoPossessAI AutoPossessAI)
{
	if (Pawn)
	{
		Pawn->AutoPossessAI = AutoPossessAI;
	}
}

void UExtendedUnrealLibrary::SetPreviewSkeletalMesh(UAnimationAsset* VertexAnimationProfileAsset, USkeletalMesh* PreviewMesh)
{
	if (IsValid(VertexAnimationProfileAsset))
	{
		VertexAnimationProfileAsset->SetPreviewMesh(PreviewMesh);
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


////bool UExtendedUnrealLibrary::IsPointInsideCollision(const UPrimitiveComponent* Component, const FVector& Point)
////{
////	if (!Component)
////	{
////		return false;
////	}
////
////	float OutSquaredDistance = -1;
////	FVector OutClosestPointOnCollision(0.f);
////	if (Component->GetSquaredDistanceToCollision(Point, OutSquaredDistance, OutClosestPointOnCollision))
////	{
////		return OutSquaredDistance < 0.0f;
////	}
////
////	return false;
////}

bool UExtendedUnrealLibrary::IsPointInsideCapsule(const UCapsuleComponent* Capsule, const FVector& Point)
{
	if (!Capsule)
	{
		return false;
	}

	const FVector Dir = Point - Capsule->GetComponentLocation();
	const FVector XYProjection(Dir.X, Dir.Y, 0.0f); // Project to XY plane

	const double HorizontalDist = XYProjection.Size();
	const double VerticalDist = FMath::Abs(Dir.Z);

	return HorizontalDist <= Capsule->GetScaledCapsuleRadius() && VerticalDist <= Capsule->GetScaledCapsuleHalfHeight();
}

UPARAM(DisplayName = "PointIsInside") bool UExtendedUnrealLibrary::IsPointInsideSphere(const USphereComponent* Sphere, const FVector& Point)
{
	if (!Sphere)
	{
		return false;
	}

	FVector SphereCenter = Sphere->GetComponentLocation();
	const double SphereRadius = Sphere->GetScaledSphereRadius();
	const double DistanceSquared = FVector::DistSquared(SphereCenter, Point);
	return DistanceSquared <= FMath::Square(SphereRadius);
}

UPARAM(DisplayName = "PointIsInside") bool UExtendedUnrealLibrary::IsPointInsideBox(const UBoxComponent* Box, const FVector& Point)
{
	if (!Box)
	{
		return false;
	}

	// Transform the point from world space to the box's local space
	const FTransform& BoxTransform = Box->GetComponentTransform();
	const FVector LocalPoint = BoxTransform.InverseTransformPosition(Point);
	const FVector BoxExtent = Box->GetScaledBoxExtent();

	// Check if the local point is within the box's local bounds
	return (LocalPoint.X >= -BoxExtent.X && LocalPoint.X <= BoxExtent.X &&
			LocalPoint.Y >= -BoxExtent.Y && LocalPoint.Y <= BoxExtent.Y &&
			LocalPoint.Z >= -BoxExtent.Z && LocalPoint.Z <= BoxExtent.Z);
}

FVector UExtendedUnrealLibrary::GetCapsuleTopLocation(const UCapsuleComponent* Capsule)
{
	if (!IsValid(Capsule))
	{
		return FVector::ZeroVector;
	}

	return Capsule->GetComponentTransform().TransformPosition(FVector(0,0, Capsule->GetUnscaledCapsuleHalfHeight()));
}

FVector UExtendedUnrealLibrary::GetCapsuleBottomLocation(const UCapsuleComponent* Capsule)
{
	if (!IsValid(Capsule))
	{
		return FVector::ZeroVector;
	}

	return Capsule->GetComponentTransform().TransformPosition(FVector(0, 0, 0 - Capsule->GetUnscaledCapsuleHalfHeight()));
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


void UExtendedUnrealLibrary::SetTimelineDuration(UTimelineComponent* Timeline, double Duration)
{
	if (IsValid(Timeline))
	{
		Timeline->SetPlayRate(Timeline->GetTimelineLength() / FMath::Max(0.001, Duration));
	}
}

double UExtendedUnrealLibrary::GetTimelineDuration(UTimelineComponent* Timeline)
{
	return IsValid(Timeline) ? Timeline->GetTimelineLength() * Timeline->GetPlayRate() : 0.0;
}

bool UExtendedUnrealLibrary::MovementComponent_IsInWater(UMovementComponent* MovementComponent)
{
	return MovementComponent ? MovementComponent->IsInWater() : false;
}

FVector UExtendedUnrealLibrary::GetLevelEditingViewportLocation(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (GCurrentLevelEditingViewportClient)
	{
		return GCurrentLevelEditingViewportClient->ViewTransformPerspective.GetLocation();
	}
#endif // WITH_EDITOR
	return FVector();
}

void UExtendedUnrealLibrary::SetLevelEditingViewportLocation(const UObject* WorldContextObject, const FVector Location)
{
#if WITH_EDITOR
	if (GCurrentLevelEditingViewportClient)
	{
		return GCurrentLevelEditingViewportClient->ViewTransformPerspective.SetLocation(Location);
	}
#endif // WITH_EDITOR
}

FRotator UExtendedUnrealLibrary::GetLevelEditingViewportRotation(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (GCurrentLevelEditingViewportClient)
	{
		return GCurrentLevelEditingViewportClient->ViewTransformPerspective.GetRotation();
	}
#endif // WITH_EDITOR
	return FRotator();
}

void UExtendedUnrealLibrary::SetLevelEditingViewportRotation(const UObject* WorldContextObject, const FRotator Rotation)
{
#if WITH_EDITOR
	if (GCurrentLevelEditingViewportClient)
	{
		return GCurrentLevelEditingViewportClient->ViewTransformPerspective.SetRotation(Rotation);
	}
#endif // WITH_EDITOR
}

void UExtendedUnrealLibrary::SceneComponentSetAbsoluteAdvanced(USceneComponent* Component, const bool bNewAbsoluteLocation, const bool bNewAbsoluteRotation, const bool bNewAbsoluteScale, const bool bMaintainWorldTransform)
{
	if (!IsValid(Component))
	{
		return;
	}

	const FTransform WorldTransform = Component->GetComponentTransform();

	Component->SetUsingAbsoluteLocation(bNewAbsoluteLocation);
	Component->SetUsingAbsoluteRotation(bNewAbsoluteRotation);
	Component->SetUsingAbsoluteScale(bNewAbsoluteScale);

	if (bMaintainWorldTransform)
	{
		Component->UpdateComponentToWorld(EUpdateTransformFlags::SkipPhysicsUpdate, ETeleportType::TeleportPhysics);
		Component->SetWorldTransform(WorldTransform, false, nullptr, ETeleportType::TeleportPhysics);
	}
	else
	{
		Component->UpdateComponentToWorld(EUpdateTransformFlags::None, ETeleportType::None);
	}
}


//void UExtendedUnrealLibrary::DelaySeconds(const UObject* WorldContextObject, double Duration, bool bRetriggerable, EDelayInput Input, FLatentActionInfo LatentInfo, EDelayOutput& Output)
//{
//	if (Input == EDelayInput::Execute)
//	{
//		Output = EDelayOutput::Completed;
//	}
//	else if (Input == EDelayInput::Cancel)
//	{
//		Output = EDelayOutput::Cancelled;
//	}
//
//	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
//	if (!World)
//	{
//		return;
//	}
//
//	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
//	FDelayAction* Action = LatentActionManager.FindExistingAction<FDelayAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);
//	if (Action == nullptr)
//	{
//		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FDelayAction(Duration, LatentInfo));
//	}
//	else if(bRetriggerable)
//	{
//		// Reset the existing delay to the new duration
//		Action->TimeRemaining = Duration;
//	}
//	else
//	{
//		Action->TimeRemaining = 0;
//		Action->NotifyActionAborted();
//	}
//}

void UExtendedUnrealLibrary::BrowseToAssets(const TArray<FAssetData>& Assets)
{
#if WITH_EDITOR
	GEditor->SyncBrowserToObjects(const_cast<TArray<FAssetData>&>(Assets));
#endif //WITH_EDITOR
}

void UExtendedUnrealLibrary::EditorRequestPlaySession(bool bSimulate)
{
#if WITH_EDITOR
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");

		FRequestPlaySessionParams SessionParams;
		SessionParams.WorldType = bSimulate ? EPlaySessionWorldType::SimulateInEditor : EPlaySessionWorldType::PlayInEditor;

		if (bSimulate)
		{
			TSharedPtr<IAssetViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveViewport();
			if (ActiveLevelViewport.IsValid())
			{
				SessionParams.DestinationSlateViewport = ActiveLevelViewport;
			}
		}
		GUnrealEd->RequestPlaySession(SessionParams);
	}
#endif //WITH_EDITOR
}

//FCollisionObjectQueryParams::InitType CollisionObjectQueryParamsInitTypeFromQueryObjectMobility(EQueryObjectMobility QueryObjectMobility)
//{
//	switch (QueryObjectMobility)
//	{
//	case EQueryObjectMobility::AllStaticObjects:	return FCollisionObjectQueryParams::InitType::AllStaticObjects;
//	case EQueryObjectMobility::AllDynamicObjects:	return FCollisionObjectQueryParams::InitType::AllDynamicObjects;
//	default:
//	case EQueryObjectMobility::AllObjects:			return FCollisionObjectQueryParams::InitType::AllObjects;
//	}
//}

void UExtendedUnrealLibrary::MarkRenderTransformDirty(UActorComponent* Component)
{
	if (IsValid(Component))
	{
		Component->MarkRenderTransformDirty();
	}
}

void UExtendedUnrealLibrary::MarkRenderStateDirty(UActorComponent* Component)
{
	if (IsValid(Component))
	{
		Component->MarkRenderStateDirty();
	}
}

bool UExtendedUnrealLibrary::GetAllowCPUAccess(const UStaticMesh* StaticMesh)
{
	return IsValid(StaticMesh) ? StaticMesh->bAllowCPUAccess : false;
}

void UExtendedUnrealLibrary::SetAllowCPUAccess(UStaticMesh* StaticMesh, const bool bAllowCPUAccess)
{
	// Only do this in the editor.
#if WITH_EDITORONLY_DATA
	if (StaticMesh)
	{
		StaticMesh->Modify();
		StaticMesh->bAllowCPUAccess = bAllowCPUAccess;
		StaticMesh->PostEditChange();
	}
#endif
}

TArray<FVector> UExtendedUnrealLibrary::FlipVectors(const TArray<FVector>& Vectors)
{
	TArray<FVector> OutVectors;
	if (Vectors.Num() > 0)
	{
		OutVectors.SetNumUninitialized(Vectors.Num());
		for (int i = 0; i < Vectors.Num(); ++i)
		{
			OutVectors[i] = -Vectors[i];
		}
	}
	return OutVectors;
}

bool UExtendedUnrealLibrary::OrientedBoxOverlapActors(const UObject* WorldContextObject, const FVector BoxPos, const FVector BoxExtent, const FRotator BoxRotation, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, TSubclassOf<AActor> ActorClassFilter, const TArray<AActor*>& ActorsToIgnore, TArray<AActor*>& OutActors)
{
	OutActors.Empty();

	TArray<UPrimitiveComponent*> OverlapComponents;
	bool bOverlapped = OrientedBoxOverlapComponents(WorldContextObject, BoxPos, BoxExtent, BoxRotation, ObjectTypes, nullptr, ActorsToIgnore, OverlapComponents);
	if (bOverlapped)
	{
		UKismetSystemLibrary::GetActorListFromComponentList(OverlapComponents, ActorClassFilter, OutActors);
	}

	return (OutActors.Num() > 0);
}

bool UExtendedUnrealLibrary::OrientedBoxOverlapComponents(const UObject* WorldContextObject, const FVector BoxPos, const FVector BoxExtent, const FRotator BoxRotation, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, TSubclassOf<UActorComponent> ComponentClassFilter, const TArray<AActor*>& ActorsToIgnore, TArray<UPrimitiveComponent*>& OutComponents)
{
	OutComponents.Empty();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(OrientedBoxOverlapComponents), false);
	Params.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;

	FCollisionObjectQueryParams ObjectParams;
	for (auto Iter = ObjectTypes.CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel& Channel = UCollisionProfile::Get()->ConvertToCollisionChannel(false, *Iter);
		ObjectParams.AddObjectTypesToQuery(Channel);
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World != nullptr)
	{
		const FQuat BoxQuat = BoxRotation.Quaternion();
		World->OverlapMultiByObjectType(
			Overlaps,
			BoxPos,
			BoxQuat,
			ObjectParams,
			FCollisionShape::MakeBox(BoxExtent),
			Params
		);
	}

	for (const FOverlapResult& O : Overlaps)
	{
		if (O.Component.IsValid())
		{
			if (!ComponentClassFilter || O.Component.Get()->IsA(ComponentClassFilter))
			{
				OutComponents.Add(O.Component.Get());
			}
		}
	}

	return (OutComponents.Num() > 0);
}

bool UExtendedUnrealLibrary::SphereOverlapComponentCollision(const UPrimitiveComponent* Component, const FVector& Point, const float Radius, FName BoneName, FVector& OutClosestPoint, double& OutDistance)
{
	if (Component)
	{
		if (FBodyInstance* BodyInst = Component->GetBodyInstance(BoneName, /*bGetWelded=*/ false))
		{
			float DistanceToPoint = BodyInst->GetDistanceToBody(Point, OutClosestPoint);
			if (DistanceToPoint >= 0)
			{
				OutDistance = FMath::Max(0, DistanceToPoint - Radius);
				return OutDistance == 0;
			}
		}
	}

	OutClosestPoint = FVector::ZeroVector;
	OutDistance = 0;
	return false;
}

bool UExtendedUnrealLibrary::GetClosestPointOnBodySetup(UBodySetup* BodySetup, const FTransform& BodyTransform, const FVector& Point, FVector& OutClosestPoint, double& DistanceSquared)
{
	if (!BodySetup)
	{
		OutClosestPoint = FVector::ZeroVector;
		DistanceSquared = 0.0;
		return false;
	}

	float ClosestDistanceSq = FLT_MAX;
	bool bFoundPoint = false;

	// Iterate over convex collision elements
	for (const FKConvexElem& ConvexElem : BodySetup->AggGeom.ConvexElems)
	{
		FVector LocalClosestPoint;
		FVector Normal;
		float Distance = ConvexElem.GetClosestPointAndNormal(Point, BodyTransform, LocalClosestPoint, Normal);

		// Check if this is the closest point so far
		float DistanceSq = Distance * Distance;
		if (DistanceSq < ClosestDistanceSq)
		{
			ClosestDistanceSq = DistanceSq;
			OutClosestPoint = LocalClosestPoint;
			bFoundPoint = true;
		}
	}

	// Iterate over sphere collision elements
	for (const FKSphereElem& SphereElem : BodySetup->AggGeom.SphereElems)
	{
		FVector SphereCenter = BodyTransform.TransformPosition(SphereElem.Center);
		FVector LocalClosestPoint = SphereCenter + (Point - SphereCenter).GetSafeNormal() * FMath::Min(SphereElem.Radius, FVector::Dist(SphereCenter, Point));
		double DistanceSq = FVector::DistSquared(Point, LocalClosestPoint);

		if (DistanceSq < ClosestDistanceSq)
		{
			ClosestDistanceSq = DistanceSq;
			OutClosestPoint = LocalClosestPoint;
			bFoundPoint = true;
		}
	}

	// Iterate over box collision elements
	for (const FKBoxElem& BoxElem : BodySetup->AggGeom.BoxElems)
	{
		FTransform BoxTransform = BodyTransform * FTransform(BoxElem.Rotation, BoxElem.Center);
		FVector LocalClosestPoint = UExtendedMathLibrary::ClosestPointOnBox(Point, BoxTransform, FVector(BoxElem.X, BoxElem.Y, BoxElem.Z) * 0.5f);
		double DistanceSq = FVector::DistSquared(Point, LocalClosestPoint);

		if (DistanceSq < ClosestDistanceSq)
		{
			ClosestDistanceSq = DistanceSq;
			OutClosestPoint = LocalClosestPoint;
			bFoundPoint = true;
		}
	}

	// Iterate over capsule (sphyl) collision elements
	for (const FKSphylElem& SphylElem : BodySetup->AggGeom.SphylElems)
	{
		FTransform SphylTransform = BodyTransform * FTransform(SphylElem.Rotation, SphylElem.Center);

		// TODO: REVIEW THIS FUNCTION. It is using the forward vector for the capsule axis. Need to ensure it is being used correctly. Ideally, the upvector would be the capsule axis.
		FVector LocalClosestPoint = UExtendedMathLibrary::ClosestPointOnCapsule(Point, SphylTransform.GetLocation(), SphylTransform.GetRotation().Rotator(), SphylElem.Radius, SphylElem.Length * 0.5f);
		double DistanceSq = FVector::DistSquared(Point, LocalClosestPoint);

		if (DistanceSq < ClosestDistanceSq)
		{
			ClosestDistanceSq = DistanceSq;
			OutClosestPoint = LocalClosestPoint;
			bFoundPoint = true;
		}
	}

	if (bFoundPoint)
	{
		DistanceSquared = ClosestDistanceSq;
	}

	return bFoundPoint;
}

bool UExtendedUnrealLibrary::GetClosestPointOnCollision(UPrimitiveComponent* Component, const FName BoneName, const FVector& Point, FVector& OutClosestPoint, double& OutDistance)
{
	if (Component->IsCollisionEnabled())
	{
		OutDistance = Component->GetClosestPointOnCollision(Point, OutClosestPoint, BoneName);
		return OutDistance >= 0;
	}
	else
	{
		double DistanceSquared = 0;
		bool bSuccess = UExtendedUnrealLibrary::GetClosestPointOnBodySetup(Component->GetBodySetup(), Component->GetComponentTransform(), Point, OutClosestPoint, DistanceSquared);
		OutDistance = FMath::Sqrt(DistanceSquared);
		return bSuccess;
	}
}

bool UExtendedUnrealLibrary::GetClosestPointOnComponentBounds(UPrimitiveComponent* Component, const FVector& Point, FVector& OutClosestPoint, double& OutDistance)
{
	if (!IsValid(Component))
	{
		OutClosestPoint = FVector::ZeroVector;
		OutDistance = -1.0;
		return false;
	}

	// Get the component's local-space bounds.
	// CalcBounds(FTransform::Identity) computes the bounds in object's local space.
	const FBoxSphereBounds LocalBounds = Component->CalcBounds(FTransform::Identity);

	if (!LocalBounds.GetBox().IsValid)
	{
		OutClosestPoint = FVector::ZeroVector;
		OutDistance = -1.0; // Indicate invalid or empty local bounds
		return false;
	}

	FOrientedBox OrientedBoundingBox;
	{
		const FTransform ComponentWorldTransform = Component->GetComponentTransform();
		OrientedBoundingBox.Center = ComponentWorldTransform.TransformPosition(LocalBounds.GetBox().GetCenter());
		OrientedBoundingBox.ExtentX = LocalBounds.GetBox().GetExtent().X;
		OrientedBoundingBox.ExtentY = LocalBounds.GetBox().GetExtent().Y;
		OrientedBoundingBox.ExtentZ = LocalBounds.GetBox().GetExtent().Z;
		OrientedBoundingBox.AxisX = ComponentWorldTransform.GetRotation().GetForwardVector();
		OrientedBoundingBox.AxisY = ComponentWorldTransform.GetRotation().GetRightVector();
		OrientedBoundingBox.AxisZ = ComponentWorldTransform.GetRotation().GetUpVector();
	}

	{
		const FTransform OBB_LocalToWorld = FTransform(OrientedBoundingBox.AxisX, OrientedBoundingBox.AxisY, OrientedBoundingBox.AxisZ, OrientedBoundingBox.Center);
		const FVector LocalPoint = OBB_LocalToWorld.InverseTransformPosition(Point);
		const FBox LocalAABB(
			FVector(-OrientedBoundingBox.ExtentX, -OrientedBoundingBox.ExtentY, -OrientedBoundingBox.ExtentZ), // Min point
			FVector(OrientedBoundingBox.ExtentX, OrientedBoundingBox.ExtentY, OrientedBoundingBox.ExtentZ)    // Max point
		);
		const FVector ClosestLocalPoint = LocalAABB.GetClosestPointTo(LocalPoint);
		OutClosestPoint = OBB_LocalToWorld.TransformPosition(ClosestLocalPoint);
	}

	OutDistance = FVector::Dist(Point, OutClosestPoint);

	return true;
}


TArray<FVectorArray> UExtendedUnrealLibrary::GetSegmentsOverlapingComponent(const TArray<FVector>& Path, const double CapsuleRadius, const double CapsuleHalfHeight, const FRotator CapsuleOrientation, UPrimitiveComponent* Component)
{
	TArray<FVectorArray> Paths;

	FVectorArray CurrentPathVectorArray;
	TArray<FVector>& CurrentPathArray = CurrentPathVectorArray.Array;


	if (!Component)
	{
		CurrentPathArray = Path;
		Paths.Add(CurrentPathVectorArray);
		return Paths;
	}


	// When Collision is enabled, we can use the default method
	TFunction<bool(UPrimitiveComponent*, const FVector&, FVector&)> GetClosestPointOnCollision;
	if (Component->IsCollisionEnabled())
	{
		// Default Physics way using Chaos Physics interface.
		GetClosestPointOnCollision = [](UPrimitiveComponent* Component, const FVector& Point, FVector& ClosestPoint)
			{
				return Component->GetClosestPointOnCollision(Point, ClosestPoint) >= 0;
			};
	}
	else
	{
		// Check 
		GetClosestPointOnCollision = [](UPrimitiveComponent* Component, const FVector& Point, FVector& ClosestPoint)
			{
				double DistanceSquared = 0.0;
				return UExtendedUnrealLibrary::GetClosestPointOnBodySetup(Component->GetBodySetup(), Component->GetComponentTransform(), Point, ClosestPoint, DistanceSquared);
			};
	}


	// Check points of the path as a capsule to see if they overlap the component's collision.
	// TODO: Consider checking between points to avoid missing overlaps.
	for (int32 i = 0; i < Path.Num(); ++i)
	{
		const FVector& Point = Path[i];
		FVector ClosestPoint;
		if (!GetClosestPointOnCollision(Component, Point, ClosestPoint))
		{
			// The Couldn't find closest point. There's no usable collision data. Return now.
			if (CurrentPathArray.Num() > 0)
			{
				CurrentPathArray = Path;
				Paths.Add(CurrentPathVectorArray);
				return Paths;
			}
		}

		const FVector OrientedSegment = CapsuleOrientation.RotateVector(FVector(0, 0, CapsuleHalfHeight));
		const bool bOverlapsRotatedCapsule = FMath::PointDistToSegment(Point, ClosestPoint - OrientedSegment, ClosestPoint + OrientedSegment) <= CapsuleRadius;

		if (bOverlapsRotatedCapsule)
		{
			CurrentPathArray.Add(Point);
		}
		else
		{
			// The point is outside the bounds of the component. Split the path here.
			if (CurrentPathArray.Num() > 0)
			{
				Paths.Add(CurrentPathVectorArray);
				CurrentPathArray.Empty();
			}
		}
	}

	// Add last remaining segment if there is one.
	if (CurrentPathArray.Num() > 0)
	{
		Paths.Add(CurrentPathVectorArray);
	}

	return Paths;
}

bool UExtendedUnrealLibrary::IsLevelNameValid(const FName LevelName)
{
	FString MapName = LevelName.ToString();
	return GEngine->MakeSureMapNameIsValid(MapName);
}

UArrowComponent* UExtendedUnrealLibrary::GetCharacterArrow(ACharacter* Target)
{
#if WITH_EDITORONLY_DATA
	if (IsValid(Target))
	{
		return Target->GetArrowComponent();
	}
#endif //WITH_EDITORONLY_DATA
	return nullptr;
}

void UExtendedUnrealLibrary::SetComponentSprite(USceneComponent* SceneComponent, UTexture2D* SpriteTexture)
{
#if WITH_EDITORONLY_DATA
	if (IsValid(SceneComponent))
	{
		// Hide scene component's current visual if we are setting our own.
		SceneComponent->bVisualizeComponent = !IsValid(SpriteTexture);

		// TODO: Get a tagged component?
		const bool bRegister = true;

		// Only spawn a sprite if we have a valid texture to show.
		if (!IsValid(SpriteTexture))
		{
			return;
		}

		// Don't spawn a component if there isn't an owner, or if this is the game world.
		if (!IsValid(SceneComponent->GetOwner()) || SceneComponent->GetWorld()->IsGameWorld())
		{
			return;
		}

		TObjectPtr<UBillboardComponent> SpriteComponent = nullptr;
		// Create a new billboard component to serve as a visualization of the actor until there is another primitive component
		{
			FCookLoadScope EditorOnlyLoadScope(ECookLoadType::EditorOnly);
			SpriteComponent = NewObject<UBillboardComponent>(SceneComponent->GetOwner(), NAME_None, RF_Transactional | RF_Transient | RF_TextExportTransient);
		}

		SpriteComponent->Sprite = SpriteTexture;
		SpriteComponent->SetRelativeScale3D_Direct(FVector(0.5f, 0.5f, 0.5f));
		SpriteComponent->Mobility = EComponentMobility::Movable;
		SpriteComponent->AlwaysLoadOnClient = false;
		SpriteComponent->SetIsVisualizationComponent(true);
		SpriteComponent->SpriteInfo.Category = TEXT("Misc");
		SpriteComponent->SpriteInfo.DisplayName = NSLOCTEXT("SpriteCategory", "Misc", "Misc");
		SpriteComponent->CreationMethod = SceneComponent->CreationMethod;
		SpriteComponent->bIsScreenSizeScaled = true;
		SpriteComponent->bUseInEditorScaling = true;
		SpriteComponent->OpacityMaskRefVal = .3f;

		SpriteComponent->SetupAttachment(SceneComponent);

		if (bRegister)
		{
			SpriteComponent->RegisterComponent();
		}
	}
#endif //WITH_EDITORONLY_DATA
}

UBillboardComponent* UExtendedUnrealLibrary::SetActorRootSprite(AActor* Target, UTexture2D* SpriteTexture)
{
#if WITH_EDITORONLY_DATA
	if (IsValid(Target) && Target->HasValidRootComponent())
	{
		USceneComponent* SceneComponent = Target->GetRootComponent();

		// Hide scene component's current visual if we are setting our own.
		SceneComponent->bVisualizeComponent = false; // !IsValid(SpriteTexture);

		// TODO: Get a tagged component?
		const bool bRegister = true;

		// Only spawn a sprite if we have a valid texture to show.
		if (!IsValid(SpriteTexture))
		{
			return nullptr;
		}

		// Don't spawn a component if there isn't an owner, or if this is the game world.
		if (Target->GetWorld()->IsGameWorld())
		{
			return nullptr;
		}

		TObjectPtr<UBillboardComponent> SpriteComponent = nullptr;
		// Create a new billboard component to serve as a visualization of the actor until there is another primitive component
		{
			FCookLoadScope EditorOnlyLoadScope(ECookLoadType::EditorOnly);
			SpriteComponent = NewObject<UBillboardComponent>(Target, NAME_None, RF_Transactional | RF_Transient | RF_TextExportTransient);
		}

		SpriteComponent->Sprite = SpriteTexture;
		SpriteComponent->SetRelativeScale3D_Direct(FVector(0.5f, 0.5f, 0.5f));
		SpriteComponent->Mobility = EComponentMobility::Movable;
		SpriteComponent->AlwaysLoadOnClient = false;
		SpriteComponent->SetIsVisualizationComponent(true);
		SpriteComponent->SpriteInfo.Category = TEXT("Misc");
		SpriteComponent->SpriteInfo.DisplayName = NSLOCTEXT("SpriteCategory", "Misc", "Misc");
		SpriteComponent->CreationMethod = SceneComponent->CreationMethod;
		SpriteComponent->bIsScreenSizeScaled = true;
		SpriteComponent->bUseInEditorScaling = true;
		SpriteComponent->OpacityMaskRefVal = .3f;

		SpriteComponent->SetupAttachment(SceneComponent);

		if (bRegister)
		{
			SpriteComponent->RegisterComponent();
		}
		return SpriteComponent;
	}
#endif //WITH_EDITORONLY_DATA
	return nullptr;
}

void UExtendedUnrealLibrary::SetTransient(UObject* Target, const bool bTransient)
{
	if (IsValid(Target))
	{
		if (bTransient)
		{
			Target->SetFlags(RF_Transient);
		}
		else
		{
			Target->ClearFlags(RF_Transient);
		}
	}
}

bool UExtendedUnrealLibrary::GetTransient(const UObject* Target)
{
	if (IsValid(Target))
	{
		return Target->HasAllFlags(RF_Transient);
	}
	return false;
}

void UExtendedUnrealLibrary::SetEditorOnlyActor(AActor* Target, const bool bIsEditorOnlyActor)
{
	if (IsValid(Target))
	{
		Target->bIsEditorOnlyActor = bIsEditorOnlyActor;
	}
}

bool UExtendedUnrealLibrary::IsEditorOnlyActor(const AActor* Target)
{
	if (IsValid(Target))
	{
		return Target->bIsEditorOnlyActor;
	}
	return false;
}

bool UExtendedUnrealLibrary::SetJumpHeight(UCharacterMovementComponent* CharacterMovement, const float JumpHeight)
{
	if (CharacterMovement)
	{
		return false;
	}

	// Use the Character's personal Gravity by default.
	float Gravity = CharacterMovement->GetGravityZ();

	// With Zero Gravity, the character will not fall back down.
	if (FMath::IsNearlyZero(Gravity))
	{
		return false;

		/*
		// Fallback to the world's current gravity
		Gravity = GetWorld()->GetGravityZ();
		if (FMath::IsNearlyZero(Gravity))
		{
			// Fallback to the game's default gravity
			Gravity = GetWorld()->GetDefaultGravityZ();
			if (FMath::IsNearlyZero(Gravity))
			{
				// With Zero Gravity, the character will not fall back down.
				return false;
			}
		}
		*/
	}

	// Jump Height is relative to the current gravity. Gravity cannot be zero. 
	CharacterMovement->JumpZVelocity = -1 * Gravity * FMath::Sqrt(2 * JumpHeight / Gravity);

	return true;
}

//void UExtendedUnrealLibrary::SetSplineComponentPointInterpMode(USplineComponent* SplineComponent, int32 PointIndex, TEnumAsByte<EInterpCurveMode> Mode, bool bUpdateSpline)
//{
//	if (!IsValid(SplineComponent))
//	{
//		return;
//	}
//
//	const int32 NumPoints = SplineComponent->SplineCurves.Position.Points.Num();
//	if ((PointIndex >= 0) && (PointIndex < NumPoints))
//	{
//		SplineComponent->SplineCurves.Position.Points[PointIndex].InterpMode = CIM_CurveUser;
//
//		if (bUpdateSpline)
//		{
//			SplineComponent->UpdateSpline();
//		}
//	}
//}

FVector UExtendedUnrealLibrary::GetCharacterOriginFromBaseLocation(const ACharacter* Target, const FVector BaseLocation)
{
	if (!IsValid(Target))
	{
		return FVector::ZeroVector;
	}

	const FVector WorldOffset = BaseLocation - GetCharacterBaseLocation(Target);
	return Target->GetActorLocation() + WorldOffset;
}

FVector UExtendedUnrealLibrary::GetCharacterBaseLocation(const ACharacter* Target)
{
	if (!IsValid(Target))
	{
		return FVector::ZeroVector;
	}

	const UCapsuleComponent* Capsule = Target->GetCapsuleComponent();
	if (!IsValid(Capsule))
	{
		return Target->GetActorLocation();
	}

	const float HalfHeight = Capsule->GetUnscaledCapsuleHalfHeight();
	return Capsule->GetComponentTransform().TransformPosition(FVector(0, 0, -HalfHeight));
}

bool UExtendedUnrealLibrary::SetCharacterBaseLocation(ACharacter* Target, const FVector BaseLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport)
{
	if (!IsValid(Target))
	{
		return false;
	}

	return Target->SetActorLocation(GetCharacterOriginFromBaseLocation(Target, BaseLocation), bSweep, &SweepHitResult, TeleportFlagToEnum(bTeleport));
}

bool UExtendedUnrealLibrary::SetCharacterBaseLocationAndRotation(ACharacter* Target, const FVector BaseLocation, FRotator BaseRotation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport)
{
	if (!IsValid(Target))
	{
		return false;
	}

	return Target->SetActorLocationAndRotation(GetCharacterOriginFromBaseLocation(Target, BaseLocation), BaseRotation, bSweep, &SweepHitResult, TeleportFlagToEnum(bTeleport));
}



TArray<AActor*> UExtendedUnrealLibrary::FindActorsByFileNames(const UObject* WorldContextObject, const TArray<FString>& FileNames)
{
    TArray<AActor*> Result;

    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    if (!World || FileNames.Num() == 0)
    {
        return Result;
    }

    // O(1) lookup
    TSet<FString> FileNamesSet(FileNames);

    for (TActorIterator<AActor> It(World); It; ++It)
    {
        AActor* Actor = *It;
        if (!IsValid(Actor))
		{
			continue;
		}

		UPackage* ActorPackage = Actor->GetExternalPackage();
		if (!IsValid(ActorPackage))
		{
			continue;
		}

		const FString ExternalActorShortName = FPaths::GetBaseFilename(ActorPackage->GetName());

		if (FileNamesSet.Contains(ExternalActorShortName))
		{
			Result.AddUnique(Actor);

			if (FileNamesSet.Num() == Result.Num())
			{
				break;
			}
		}
    }

    return Result;
}

void UExtendedUnrealLibrary::ProceduralMesh_SetUseComplexAsSimpleCollision(UProceduralMeshComponent* Target, bool bUseComplexAsSimpleCollision)
{
	if (IsValid(Target))
	{
		Target->bUseComplexAsSimpleCollision = bUseComplexAsSimpleCollision;
	}
}

void UExtendedUnrealLibrary::RegisterReferencedObject(UObject* WorldContext, UObject* Object)
{
	if (!Object)
	{
		ensureMsgf(Object != nullptr, TEXT("RegisterReferencedObject: Object is not valid."));
		return;
	}

	if (Object->IsA<AActor>())
	{
		const AActor* Actor = Cast<AActor>(Object);
		UE_LOG(LogExtendedUnreal, Warning, TEXT("RegisterReferencedObject: Object '%s' is an Actor. Actors are not allowed to be registered."), *Actor->GetName());
		return;
	}
	if (Object->IsA<UActorComponent>())
	{
		const UActorComponent* Comp = Cast<UActorComponent>(Object);
		FString OwnerName = Comp->GetOwner() ? Comp->GetOwner()->GetName() : TEXT("None");
		UE_LOG(LogExtendedUnreal, Warning, TEXT("RegisterReferencedObject: Object `%s`:'%s' is a Component. Components are not allowed to be registered."), *OwnerName, *Comp->GetName());
		return;
	}

	const UWorld* World = GEngine->GetWorldFromContextObject(Object, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		UE_LOG(LogExtendedUnreal, Warning, TEXT("RegisterReferencedObject: World is not valid."));
		return;
	}

	UGameInstance* GameInstance = World->GetGameInstance();
	if (!GameInstance)
	{
		UE_LOG(LogExtendedUnreal, Warning, TEXT("RegisterReferencedObject: GameInstance is not valid."));
		return;
	}

	// Register the object with the game instance
	GameInstance->RegisterReferencedObject(Object);
}

void UExtendedUnrealLibrary::UnregisterReferencedObject(UObject* WorldContext, UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogExtendedUnreal, Warning, TEXT("UnregisterReferencedObject: Object is not valid"));
		return;
	}

	// Don't allow actors or components
	if (Object->IsA<AActor>())
	{
		const AActor* Actor = Cast<AActor>(Object);
		UE_LOG(LogExtendedUnreal, Warning, TEXT("UnregisterReferencedObject: Object '%s' is an Actor. Actors are not allowed to be registered."), *Actor->GetName());
		return;
	}
	if (Object->IsA<UActorComponent>())
	{
		const UActorComponent* Comp = Cast<UActorComponent>(Object);
		FString OwnerName = Comp->GetOwner() ? Comp->GetOwner()->GetName() : TEXT("None");
		UE_LOG(LogExtendedUnreal, Warning, TEXT("UnregisterReferencedObject: Object `%s`:'%s' is a Component. Components are not allowed to be registered."), *OwnerName, *Comp->GetName());
		return;
	}

	const UWorld* World = GEngine->GetWorldFromContextObject(Object, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		UE_LOG(LogExtendedUnreal, Warning, TEXT("UnregisterReferencedObject: World is not valid."));
		return;
	}

	UGameInstance* GameInstance = World->GetGameInstance();
	if (!GameInstance)
	{
		UE_LOG(LogExtendedUnreal, Warning, TEXT("UnregisterReferencedObject: GameInstance is not valid."));
		return;
	}

	// Unregister the object from the game instance
	GameInstance->UnregisterReferencedObject(Object);
}

bool UExtendedUnrealLibrary::OpenDirectoryInFileSystem(const FString& DirectoryPath)
{
	if (FPaths::DirectoryExists(DirectoryPath))
	{
		FPlatformProcess::ExploreFolder(*DirectoryPath);
		return true;
	}
	else
	{
		UE_LOG(LogExtendedUnreal, Warning, TEXT("OpenDirectoryInFileSystem: Could not open directory, it does not exist: %s"), *DirectoryPath);
		return false;
	}
}

void UExtendedUnrealLibrary::ModifyAndCompileBlueprintClass(UClass* Class)
{
#if WITH_EDITOR
	if (!IsValid(Class)) return;

	UObject* CDO = Class->GetDefaultObject();
	if (!IsValid(CDO)) return;

	CDO->Modify();

	if (UBlueprintGeneratedClass* BPGC = Cast<UBlueprintGeneratedClass>(Class))
	{
		if (UBlueprint* Blueprint = Cast<UBlueprint>(BPGC->ClassGeneratedBy))
		{
			Blueprint->Modify();
			FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
			FKismetEditorUtilities::CompileBlueprint(Blueprint);
			Blueprint->MarkPackageDirty();
		}
	}
#endif
}

bool UExtendedUnrealLibrary::GetShaderCompilingStats(int32& TotalShadersCompiled, int32& LocalWorkersCount, int32& PendingJobsCount, int32& OutstandingJobsCount, int32& ExternalJobsCount, int32& RemainingJobsCount, bool& bHasShaderJobs, bool& bIsCompiling)
{
	if (GShaderCompilingManager)
	{
		{
			FShaderCompilerStats Stats;
			GShaderCompilingManager->GetLocalStats(Stats);
			TotalShadersCompiled = Stats.GetTotalShadersCompiled();

			////const TSparseArray<TMap<FString, FShaderStats>>& ShaderCompilerStats = Stats.GetShaderCompilerStats();
			////for (const TMap<FString, FShaderStats>& Map : ShaderCompilerStats)
			////{
			////	for (const TPair<FString, FShaderStats>& ShaderStatsPair : Map)
			////	{
			////		const FString& ShaderStatsKey = ShaderStatsPair.Key;
			////		const FShaderStats& ShaderStats = ShaderStatsPair.Value;
			////		ShaderStats.Compiled;
			////		ShaderStats.Cooked;
			////		ShaderStats.CompileTime;
			////		ShaderStats.CompiledDouble;
			////		ShaderStats.CompileTime;
			////		ShaderStats.PermutationCompilations;
			////	}
			////}
			////TSharedPtr<FJsonObject> Json = Stats.ToJson();
		}

		LocalWorkersCount = GShaderCompilingManager->GetNumLocalWorkers();
		OutstandingJobsCount = GShaderCompilingManager->GetNumOutstandingJobs();
		PendingJobsCount = GShaderCompilingManager->GetNumPendingJobs();
		RemainingJobsCount = GShaderCompilingManager->GetNumRemainingJobs();
		ExternalJobsCount = RemainingJobsCount - OutstandingJobsCount;

		bHasShaderJobs = GShaderCompilingManager->HasShaderJobs();
		bIsCompiling = GShaderCompilingManager->IsCompiling();
		return true;
	}
	else
	{
		TotalShadersCompiled = 0;
		LocalWorkersCount = 0;
		OutstandingJobsCount = 0;
		PendingJobsCount = 0;
		RemainingJobsCount = 0;
		bHasShaderJobs = false;
		bIsCompiling = false;
		return false;
	}
}

bool UExtendedUnrealLibrary::GetStaticSwitchBoolOverride(const UMaterialInstance* MaterialInstance, const FName ParameterName, bool& bValue)
{
	if (!MaterialInstance)
	{
		bValue = false;
		return false;
	}

	const FStaticParameterSet& StaticParameters = MaterialInstance->GetStaticParameters();
	for (const FStaticSwitchParameter& Param : StaticParameters.StaticSwitchParameters)
	{
		if (Param.ParameterInfo.Name == ParameterName)
		{
			bValue = Param.Value;
			return true;
		}
	}

	bValue = false;
	return false;
}

bool UExtendedUnrealLibrary::GetStaticSwitchBoolValue(const UMaterialInterface* MaterialInterface, const FName ParameterName, bool& bValue)
{
	if (!MaterialInterface)
	{
		bValue = false;
		return false;
	}

	const UMaterialInterface* Current = MaterialInterface;
	while (Current)
	{
		// Check if it's a material instance first
		if (const UMaterialInstance* MI = Cast<UMaterialInstance>(Current))
		{
			if (GetStaticSwitchBoolOverride(MI, ParameterName, bValue))
			{
				return true;
			}
			Current = MI->Parent;
		}
		else if (const UMaterial* BaseMat = Cast<UMaterial>(Current))
		{
			////// This code only works in editor
			////#if WITH_EDITORONLY_DATA
			////TArray<UMaterialExpressionStaticSwitchParameter*> Switches;
			////BaseMat->GetAllExpressionsInMaterialAndFunctionsOfType(Switches);
			////
			////for (auto* Expr : Switches)
			////{
			////	if (Expr && Expr->ParameterName == ParameterName)
			////	{
			////		// reached base material and found the static switch parameter.
			////		bValue = Expr->DefaultValue;
			////		return true;
			////	}
			////}
			////#endif //WITH_EDITORONLY_DATA

			// reached base material but didn't find the parameter
			bValue = false;
			return false;
		}
		else
		{
			// unknown material type
			bValue = false;
			return false;
		}
	}

	bValue = false;
	return false;
}

void UExtendedUnrealLibrary::PlayWorldCameraShakeAdvanced(const UObject* WorldContextObject, TSubclassOf<class UCameraShakeBase> Shake, FVector Epicenter, float InnerRadius, float OuterRadius, float Falloff, bool bOrientShakeTowardsEpicenter, float Strength)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World != nullptr)
	{
		//float APlayerCameraManager::CalcRadialShakeScale(APlayerCameraManager * Camera, FVector Epicenter, float InnerRadius, float OuterRadius, float Falloff)
		const auto CalcRadialShakeScale = [](APlayerCameraManager* Camera, FVector Epicenter, float InnerRadius, float OuterRadius, float Falloff) -> float
			{
				// using camera location so stuff like spectator cameras get shakes applied sensibly as well
				// need to ensure server has reasonably accurate camera position
				FVector POVLoc = Camera->GetCameraLocation();

				if (InnerRadius < OuterRadius)
				{
					float DistPct = ((Epicenter - POVLoc).Size() - InnerRadius) / (OuterRadius - InnerRadius);
					DistPct = 1.f - FMath::Clamp(DistPct, 0.f, 1.f);
					return FMath::Pow(DistPct, Falloff);
				}
				else
				{
					// ignore OuterRadius and do a cliff falloff at InnerRadius
					return ((Epicenter - POVLoc).SizeSquared() < FMath::Square(InnerRadius)) ? 1.f : 0.f;
				}
			};

		//APlayerCameraManager::PlayWorldCameraShake(World, Shake, Epicenter, InnerRadius, OuterRadius, Falloff, bOrientShakeTowardsEpicenter);
		const auto PlayWorldCameraShake = [CalcRadialShakeScale, Strength](UWorld* InWorld, TSubclassOf<class UCameraShakeBase> Shake, FVector Epicenter, float InnerRadius, float OuterRadius, float Falloff, bool bOrientShakeTowardsEpicenter)
			{
				for (FConstPlayerControllerIterator Iterator = InWorld->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					APlayerController* PlayerController = Iterator->Get();
					if (PlayerController && PlayerController->PlayerCameraManager != NULL)
					{
						float ShakeScale = Strength * CalcRadialShakeScale(PlayerController->PlayerCameraManager, Epicenter, InnerRadius, OuterRadius, Falloff);

						if (bOrientShakeTowardsEpicenter && PlayerController->GetPawn() != NULL)
						{
							const FVector CamLoc = PlayerController->PlayerCameraManager->GetCameraLocation();
							PlayerController->ClientStartCameraShake(Shake, ShakeScale, ECameraShakePlaySpace::UserDefined, (Epicenter - CamLoc).Rotation());
						}
						else
						{
							PlayerController->ClientStartCameraShake(Shake, ShakeScale);
						}
					}
				}
			};

		PlayWorldCameraShake(World, Shake, Epicenter, InnerRadius, OuterRadius, Falloff, bOrientShakeTowardsEpicenter);
	}
}

bool UExtendedUnrealLibrary::PredictActorPath(const UObject* WorldContextObject, AActor* Actor, float PredictionTime, FPredictActorPathResult& OutResult, bool bTracePath, float ClampInitialVelocity, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, float DrawDebugTime, float SimFrequency)
{
	// Validate inputs
	if (!Actor || PredictionTime <= 0.f)
	{
		OutResult = FPredictActorPathResult();
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		OutResult = FPredictActorPathResult();
		return false;
	}

	UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
	if (!Component)
	{
		OutResult = FPredictActorPathResult();
		return false;
	}

	// Determine if we should use projectile motion
	auto ShouldUseProjectileMotion = [Actor]() -> bool
		{
			// Check if it's a falling character
			if (ACharacter* Character = Cast<ACharacter>(Actor))
			{
				if (UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement())
				{
					if (MoveComp->IsFalling())
					{
						return true;
					}
				}
			}

			// Check if physics object with gravity enabled
			if (UPrimitiveComponent* RootPrimitive = Cast<UPrimitiveComponent>(Actor->GetRootComponent()))
			{
				if (RootPrimitive->IsSimulatingPhysics() && RootPrimitive->IsGravityEnabled())
				{
					return true;
				}
			}

			return false;
		};

	FVector StartLocation = Actor->GetActorLocation();
	FVector CurrentVelocity = Actor->GetVelocity();
	if(ClampInitialVelocity > 0)
	{
		CurrentVelocity = CurrentVelocity.GetClampedToMaxSize(ClampInitialVelocity);
	}
	FQuat Rotation = Actor->GetActorQuat();

	// Setup collision query params
	FComponentQueryParams QueryParams(SCENE_QUERY_STAT(PredictActorPath));
	QueryParams.AddIgnoredComponent(Component);
	QueryParams.AddIgnoredActor(Actor);
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	bool bUseProjectileMotion = ShouldUseProjectileMotion();

	// ========== PROJECTILE MOTION PATH ==========
	if (bUseProjectileMotion)
	{
		FVector CurrentLocation = StartLocation;
		float GravityZ = World->GetGravityZ();

		// Time step for simulation
		const float TimeStep = 1.0f / FMath::Max(SimFrequency, 1.0f);
		const int32 MaxSteps = FMath::CeilToInt(PredictionTime / TimeStep);

		float ElapsedTime = 0.f;
		bool bHitSomething = false;
		FHitResult FinalHit;

		if (bTracePath)
		{
			OutResult.PathPositions.Empty(MaxSteps + 1);
			OutResult.PathPositions.Add(CurrentLocation);
		}

		// Simulate projectile motion step by step
		for (int32 Step = 0; Step < MaxSteps; ++Step)
		{
			float DeltaTime = FMath::Min(TimeStep, PredictionTime - ElapsedTime);

			// Calculate next position using kinematic equation
			FVector NextLocation = CurrentLocation + (CurrentVelocity * DeltaTime);

			// Apply gravity to velocity for next iteration
			CurrentVelocity.Z += GravityZ * DeltaTime;

			// Sweep component along path
			TArray<FHitResult> OutHits;
			World->ComponentSweepMulti(OutHits, Component, CurrentLocation, NextLocation, Rotation, QueryParams);

			// Find first blocking hit
			bool bHitThisStep = false;
			for (const FHitResult& Hit : OutHits)
			{
				if (Hit.bBlockingHit)
				{
					bHitSomething = true;
					bHitThisStep = true;
					FinalHit = Hit;
					OutResult.PredictedLocation = Hit.Location;
					OutResult.TimeToHit = ElapsedTime + (DeltaTime * Hit.Time);

					if (bTracePath)
					{
						OutResult.PathPositions.Add(Hit.Location);
					}

					break;
				}
			}

			if (bHitThisStep)
			{
				break;
			}

			CurrentLocation = NextLocation;
			ElapsedTime += DeltaTime;

			if (bTracePath)
			{
				OutResult.PathPositions.Add(CurrentLocation);
			}

			if (ElapsedTime >= PredictionTime)
			{
				break;
			}
		}

		// Fill result
		OutResult.bBlockingHit = bHitSomething;
		OutResult.HitResult = FinalHit;

		if (!bHitSomething)
		{
			OutResult.PredictedLocation = CurrentLocation;
			OutResult.TimeToHit = PredictionTime;
		}

		// Draw debug
#if ENABLE_DRAW_DEBUG
		if (DrawDebugType != EDrawDebugTrace::None)
		{
			const bool bPersistentLines = DrawDebugType == EDrawDebugTrace::Persistent;
			const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawDebugTime : 0.f;

			// Draw path
			if (bTracePath && OutResult.PathPositions.Num() > 1)
			{
				for (int32 i = 0; i < OutResult.PathPositions.Num() - 1; ++i)
				{
					DrawDebugLine(World, OutResult.PathPositions[i], OutResult.PathPositions[i + 1],
						bHitSomething ? FColor::Red : FColor::Green, bPersistentLines, LifeTime, 0, 2.0f);
				}
			}

			// Draw final position
			DrawDebugSphere(World, OutResult.PredictedLocation, 30.0f, 12,
				bHitSomething ? FColor::Red : FColor::Green, bPersistentLines, LifeTime);

			if (bHitSomething)
			{
				DrawDebugPoint(World, FinalHit.ImpactPoint, 15.0f, FColor::Red, bPersistentLines, LifeTime);
				DrawDebugLine(World, FinalHit.ImpactPoint, FinalHit.ImpactPoint + FinalHit.ImpactNormal * 50.0f,
					FColor::Yellow, bPersistentLines, LifeTime, 0, 2.0f);
			}
		}
#endif

		return bHitSomething;
	}

	// ========== LINEAR MOTION PATH ==========
	else
	{
		FVector EndLocation = StartLocation + (CurrentVelocity * PredictionTime);

		// Perform component sweep
		TArray<FHitResult> OutHits;
		World->ComponentSweepMulti(OutHits, Component, StartLocation, EndLocation, Rotation, QueryParams);

		// Find first blocking hit
		bool bHit = false;
		FHitResult HitResult;
		for (const FHitResult& Hit : OutHits)
		{
			if (Hit.bBlockingHit)
			{
				bHit = true;
				HitResult = Hit;
				break;
			}
		}

		// Fill output result
		OutResult.bBlockingHit = bHit;
		OutResult.HitResult = HitResult;
		OutResult.PredictedLocation = bHit ? HitResult.Location : EndLocation;
		OutResult.TimeToHit = bHit ? (PredictionTime * HitResult.Time) : PredictionTime;

		if (bTracePath)
		{
			OutResult.PathPositions.Empty(2);
			OutResult.PathPositions.Add(StartLocation);
			OutResult.PathPositions.Add(OutResult.PredictedLocation);
		}

		// Draw debug visualization
#if ENABLE_DRAW_DEBUG
		if (DrawDebugType != EDrawDebugTrace::None)
		{
			const bool bPersistentLines = DrawDebugType == EDrawDebugTrace::Persistent;
			const float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawDebugTime : 0.f;

			DrawDebugLine(World, StartLocation, OutResult.PredictedLocation,
				bHit ? FColor::Red : FColor::Green, bPersistentLines, LifeTime, 0, 2.0f);

			DrawDebugSphere(World, OutResult.PredictedLocation, 30.0f, 12,
				bHit ? FColor::Red : FColor::Green, bPersistentLines, LifeTime);

			if (bHit)
			{
				DrawDebugPoint(World, HitResult.ImpactPoint, 15.0f, FColor::Red, bPersistentLines, LifeTime);
				DrawDebugLine(World, HitResult.ImpactPoint, HitResult.ImpactPoint + HitResult.ImpactNormal * 50.0f,
					FColor::Yellow, bPersistentLines, LifeTime, 0, 2.0f);
			}
		}
#endif

		return bHit;
	}
}
