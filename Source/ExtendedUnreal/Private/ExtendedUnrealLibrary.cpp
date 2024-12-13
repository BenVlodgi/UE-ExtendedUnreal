// Copyright 2023 Dream Seed LLC.

#include "ExtendedUnrealLibrary.h"


#include "ExtendedUnrealModule.h"
#include "ExtendedMathLibrary.h"
#include "Structs/DelegateHandleWrapper.h"

#if WITH_EDITOR
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#include "LevelEditorViewport.h"
#include "LevelEditor.h"
#endif

#include "UObject/NameTypes.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicsEngine/BodySetup.h"
#include "PhysicsEngine/ConvexElem.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/MovementComponent.h"
#include "Styling/SlateIconFinder.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "DelayAction.h"
#include "RuntimeErrors.h"
#include "Engine/TextureRenderTargetCube.h"
#include "TextureResource.h"
#include "ClearQuad.h"
#include "RHIContext.h"
#include "RHIUtilities.h"
#include "Kismet/GameplayStatics.h"


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

int32 UExtendedUnrealLibrary::ExtendedHashCombine(const int32 A, const int32 B)
{
	return HashCombine(A, B);
}

int32 UExtendedUnrealLibrary::ExtendedHashCombineFast(int32 A, int32 B)
{
	return HashCombineFast(A, B);;
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

void UExtendedUnrealLibrary::CopyOverParameterOverrides(UMaterialInstanceDynamic* Target, const UMaterialInstance* MaterialInstance)
{
	LLM_SCOPE(ELLMTag::MaterialInstance);

	if (!ensureAsRuntimeWarning(Target != nullptr && MaterialInstance != nullptr))
	{
		return;
	}

	for (const auto& Parameter : MaterialInstance->VectorParameterValues) Target->SetVectorParameterValueByInfo(Parameter.ParameterInfo, Parameter.ParameterValue);
	for (const auto& Parameter : MaterialInstance->DoubleVectorParameterValues) Target->SetDoubleVectorParameterValue(Parameter.ParameterInfo.Name, Parameter.ParameterValue);
	for (const auto& Parameter : MaterialInstance->ScalarParameterValues) Target->SetScalarParameterValueByInfo(Parameter.ParameterInfo, Parameter.ParameterValue);
	for (const auto& Parameter : MaterialInstance->TextureParameterValues) Target->SetTextureParameterValueByInfo(Parameter.ParameterInfo, Parameter.ParameterValue);
	for (const auto& Parameter : MaterialInstance->FontParameterValues) Target->SetFontParameterValue(Parameter.ParameterInfo.Name, Parameter.FontValue, Parameter.FontPage);

#if WITH_EDITOR
	FObjectCacheEventSink::NotifyReferencedTextureChanged_Concurrent(Target);
#endif

	////Target->InitResources();
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


UTextureRenderTargetCube* UExtendedUnrealLibrary::CreateRenderTargetCube(UObject* WorldContextObject, int32 Width, FLinearColor ClearColor, bool bAutoGenerateMipMaps, bool bSupportUAVs, bool bHDR, bool bForceLinearGamma)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	if (Width > 0 && World)
	{
		UTextureRenderTargetCube* NewRenderTargetCube = NewObject<UTextureRenderTargetCube>(WorldContextObject);
		check(NewRenderTargetCube);
		//NewRenderTargetCube->RenderTargetFormat = Format;
		NewRenderTargetCube->ClearColor = ClearColor;
		//NewRenderTargetCube->bAutoGenerateMips = bAutoGenerateMipMaps;
		NewRenderTargetCube->bCanCreateUAV = bSupportUAVs;
		NewRenderTargetCube->InitAutoFormat(Width);
		NewRenderTargetCube->UpdateResourceImmediate(true);
		NewRenderTargetCube->bHDR = true;
		////NewRenderTargetCube->OverrideFormat = PF_Unknown;
		NewRenderTargetCube->bForceLinearGamma = true;

		return NewRenderTargetCube;
	}

	return nullptr;
}

void UExtendedUnrealLibrary::ClearRenderTargetCube(UObject* WorldContextObject, UTextureRenderTargetCube* TextureRenderTargetCube, FLinearColor ClearColor)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	if (TextureRenderTargetCube
		&& TextureRenderTargetCube->GetResource()
		&& World)
	{
		////FTextureRenderTargetResource* RenderTargetResource = TextureRenderTargetCube->GameThread_GetRenderTargetResource();
		////ENQUEUE_RENDER_COMMAND(ClearRTCommand)(
		////	[RenderTargetResource, ClearColor](FRHICommandList& RHICmdList)
		////	{
		////		FRHIRenderPassInfo RPInfo(RenderTargetResource->GetRenderTargetTexture(), ERenderTargetActions::DontLoad_Store);
		////		RHICmdList.Transition(FRHITransitionInfo(RenderTargetResource->GetRenderTargetTexture(), ERHIAccess::Unknown, ERHIAccess::RTV));
		////		RHICmdList.BeginRenderPass(RPInfo, TEXT("ClearRT"));
		////		DrawClearQuad(RHICmdList, ClearColor);
		////		RHICmdList.EndRenderPass();
		////		
		////		RHICmdList.Transition(FRHITransitionInfo(RenderTargetResource->GetRenderTargetTexture(), ERHIAccess::RTV, ERHIAccess::SRVMask));
		////	});
	}
}

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

bool UExtendedUnrealLibrary::SphereOverlapComponentCollision(const UPrimitiveComponent* Component, const FVector& Point, const float Radius, FName BoneName, FVector& OutPointOnBody, float& Distance)
{
	if (Component)
	{
		if (FBodyInstance* BodyInst = Component->GetBodyInstance(BoneName, /*bGetWelded=*/ false))
		{
			float DistanceToPoint = BodyInst->GetDistanceToBody(Point, OutPointOnBody);
			if (DistanceToPoint >= 0)
			{
				Distance = FMath::Max(0, DistanceToPoint - Radius);
				return Distance == 0;
			}
		}
	}

	OutPointOnBody = FVector::ZeroVector;
	Distance = 0;
	return false;
}


bool UExtendedUnrealLibrary::GetClosestPointOnCollision(UPrimitiveComponent* Component, const FName BoneName, const FVector& Point, FVector& OutPointOnCollision, double& Distance)
{
	if (Component->IsCollisionEnabled())
	{
		Distance = Component->GetClosestPointOnCollision(Point, OutPointOnCollision, BoneName);
		return Distance >= 0;
	}
	else
	{
		double DistanceSquared = 0;
		bool bSuccess = UExtendedUnrealLibrary::GetClosestPointOnBodySetup(Component->GetBodySetup(), Component->GetComponentTransform(), Point, OutPointOnCollision, DistanceSquared);
		Distance = FMath::Sqrt(DistanceSquared);
		return bSuccess;
	}
}

bool UExtendedUnrealLibrary::GetClosestPointOnBodySetup(UBodySetup* BodySetup, const FTransform& BodyTransform, const FVector& Point, FVector& ClosestPoint, double& DistanceSquared)
{
	if (!BodySetup)
	{
		ClosestPoint = FVector::ZeroVector;
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
			ClosestPoint = LocalClosestPoint;
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
			ClosestPoint = LocalClosestPoint;
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
			ClosestPoint = LocalClosestPoint;
			bFoundPoint = true;
		}
	}

	// Iterate over capsule (sphyl) collision elements
	for (const FKSphylElem& SphylElem : BodySetup->AggGeom.SphylElems)
	{
		FTransform SphylTransform = BodyTransform * FTransform(SphylElem.Rotation, SphylElem.Center);
		FVector LocalClosestPoint = UExtendedMathLibrary::ClosestPointOnCapsule(Point, SphylTransform.GetLocation(), SphylTransform.GetRotation().Rotator(), SphylElem.Radius, SphylElem.Length * 0.5f);
		double DistanceSq = FVector::DistSquared(Point, LocalClosestPoint);

		if (DistanceSq < ClosestDistanceSq)
		{
			ClosestDistanceSq = DistanceSq;
			ClosestPoint = LocalClosestPoint;
			bFoundPoint = true;
		}
	}

	if (bFoundPoint)
	{
		DistanceSquared = ClosestDistanceSq;
	}

	return bFoundPoint;
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
