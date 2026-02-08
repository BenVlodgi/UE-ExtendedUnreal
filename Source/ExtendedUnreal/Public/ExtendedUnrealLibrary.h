// Copyright 2025 Dream Seed LLC.

#pragma once

#include "Enums/WorldType.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


#include "ExtendedUnrealLibrary.generated.h"


//UENUM()
//enum class EDelayInput : uint8
//{
//	Execute,
//	Cancel,
//};
//
//UENUM()
//enum class EDelayOutput : uint8
//{
//	Completed,
//	Cancelled,
//};

UENUM()
enum class EQueryObjectMobility : uint8
{
	AllObjects = 3,
	AllStaticObjects = 1,
	AllDynamicObjects = 2,
};

USTRUCT(BlueprintType)
struct FPredictActorPathResult
{
	GENERATED_BODY()
	
public:
	/** The final predicted location of the actor */
	UPROPERTY(BlueprintReadWrite)
	FVector PredictedLocation = FVector::ZeroVector;

	/** True if the prediction hit something during the sweep */
	UPROPERTY(BlueprintReadWrite)
	bool bBlockingHit = false;

	/** Hit result information if a blocking hit occurred */
	UPROPERTY(BlueprintReadWrite)
	FHitResult HitResult;

	/** Time elapsed before hit (or total prediction time if no hit) */
	UPROPERTY(BlueprintReadWrite)
	float TimeToHit = 0.0f;

	/** Array of positions along the predicted path (for projectile motion) */
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> PathPositions;
};



UCLASS()
class EXTENDEDUNREAL_API UExtendedUnrealLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = "Editor")
	//static void ExploreFolders();

	UFUNCTION(BlueprintPure, Category = "Widget|Brush", meta = (Keywords = "get"))
	static UPARAM(DisplayName = "Brush") FSlateBrush MakeBrushFromAppStyle(const FName Name);

	UFUNCTION(BlueprintPure, Category = "Widget|Brush", meta = (Keywords = "get", StyleSetName = "CoreStyle"))
	static UPARAM(DisplayName = "Brush") FSlateBrush MakeBrushFromStyleSet(const FName StyleSetName, const FName Name);

	UFUNCTION(BlueprintPure, Category = "Widget|Brush", meta = (Keywords = "get"))
	static UPARAM(DisplayName = "Brush") FSlateBrush MakeBrushFromSlateIcon(const FName Name);

	//UFUNCTION(BlueprintPure, Category = "Widget|Brush")
	//static UPARAM(DisplayName = "Brush") FSlateBrush MakeBrushFromSVGPath(const FString SVGPath, const FVector2D& InImageSize = FVector2D(16.0f, 16.0f));

	UFUNCTION(BlueprintPure, Category = "Utilities", meta = (DisplayName = "Get Soft Class Name"))
	static UPARAM(DisplayName = "Name") FName GetSoftClassName(const TSoftClassPtr<UObject>& Class);

	UFUNCTION(BlueprintPure, Category = "Utilities", meta = (DisplayName = "Get Soft Class Display Name Text", DevelopmentOnly))
	static UPARAM(DisplayName = "DisplayName") FText GetSoftClassDisplayNameText(const TSoftClassPtr<UObject>& Class);

	UFUNCTION(BlueprintPure, Category = "Utilities", meta = (DisplayName = "Get Class Display Name Text", DevelopmentOnly))
	static UPARAM(DisplayName = "DisplayName") FText GetClassDisplayNameText(const UClass* Class);

	UFUNCTION(BlueprintPure, Category = "Utilities", meta = (DisplayName = "Get Soft Object Name"))
	static UPARAM(DisplayName = "Name") FName GetSoftObjectName(const TSoftObjectPtr<UObject>& Object);

	/*
	 * Get Component from Base Component reference.
	 * If Actor reference is not set, FallbackActor will be used.
	 */
	UFUNCTION(BlueprintCallable, Category = "Utilities", meta = (DefaultToSelf = "FallbackActor", DisplayName = "Get Component"))
	static UPARAM(DisplayName = "Component") UActorComponent* GetBaseComponentReferenceComponent(UPARAM(ref) const FBaseComponentReference& Target, AActor* FallbackActor);

	/*
	 * Get Component from Hard Component reference.
	 * If Actor reference is not set, FallbackActor will be used.
	 */
	UFUNCTION(BlueprintCallable, Category = "Utilities", meta = (DefaultToSelf = "FallbackActor", DisplayName = "Get Component"))
	static UPARAM(DisplayName = "Component") UActorComponent* GetComponentReferenceComponent(UPARAM(ref) const FComponentReference& Target, AActor* FallbackActor);

	/*
	 * Get Component from Soft Component reference.
	 * If Actor reference is not set, FallbackActor will be used.
	 */
	UFUNCTION(BlueprintCallable, Category = "Utilities", meta = (DefaultToSelf = "FallbackActor", DisplayName = "Get Component"))
	static UPARAM(DisplayName = "Component") UActorComponent* GetSoftComponentReferenceComponent(UPARAM(ref) const FSoftComponentReference& Target, AActor* FallbackActor);

	/*
	 * Make Component reference from Component.
	 * If Actor reference is not set, FallbackActor will be used.
	 */
	UFUNCTION(BlueprintCallable, Category = "Utilities")
	static UPARAM(DisplayName = "ComponentReference") FComponentReference MakeComponentReference(const UActorComponent* Component);

	/** Searches components array and returns first encountered component with the specified name. */
	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (DefaultToSelf = "Target", ComponentClass = "/Script/Engine.ActorComponent", ComponentName, DeterminesOutputType = "ComponentClass", keywords = "find"))
	static UPARAM(DisplayName = "Component") UActorComponent* GetComponentByName(AActor* Target, TSubclassOf<UActorComponent> ComponentClass, FName ComponentName, bool bIncludeChildActors = false);

	/**
	 * Takes a string and breaks it down into a human readable string.
	 * Example - "bCreateSomeStuff" becomes "Create Some Stuff?" and "DrawScale3D" becomes "Draw Scale 3D".
	 *
	 * @param	DisplayString	The name to sanitize
	 * @param	bIsBool			True if the name is a bool
	 *
	 * @return	the sanitized version of the display name
	 */
	UFUNCTION(BlueprintCallable, Category = "Utilities|String")
	static void ToDisplayString(const FString String, FString& DisplayString, const bool bIsBool = false);


	UFUNCTION(BlueprintCallable, Category = "Level Editor", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", HidePin = "WorldContextObject", DevelopmentOnly))
	static void FocusViewportToSelection(const UObject* WorldContextObject);

	//UFUNCTION(BlueprintCallable, Category = "Level Editor", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", HidePin = "WorldContextObject", DevelopmentOnly))
	//static void FocusViewportToActor(const UObject* WorldContextObject);

	//UFUNCTION(BlueprintCallable, Category = "Physics")
	//static void SetConstraintMaxForce(UPhysicsConstraintComponent* PhysicsConstraintComponent, double MaxForceX, double MaxForceY, double MaxForceZ);

	/**
	 * Get all Actors attached to the targe which are of the given class type.
	 */
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", Class = "/Script/Engine.Actor", DeterminesOutputType = "Class", Category = "Actor", keywords = "find"))
	static UPARAM(DisplayName = "AttachedActors") TArray<AActor*> GetAttachedActorsOfClass(const AActor* Target, TSubclassOf<AActor> Class, bool bRecursivelyIncludeAttachedActors);

	static void GetAttachedActorsOfClass_InternalAppend(const AActor* Target, TSubclassOf<AActor> Class, TArray<AActor*>& AttachedActors, bool bRecursivelyIncludeAttachedActors);

	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", Class = "/Script/Engine.Actor", DeterminesOutputType = "Class", Category = "Actor", keywords = "find"))
	static UPARAM(DisplayName = "FirstAttachedActor") AActor* GetFirstAttachedActorOfClass(const AActor* Target, TSubclassOf<AActor> Class);

	/**
	 * Sets whether the component is active or not.
	 * If called during construction, will set AutoActivate.
	 * @param bNewActive - The new active state of the component
	 */
	UFUNCTION(BlueprintCallable, Category = "Components|Activation", meta = (DefaultToSelf = "Component", DisplayName = "Set Active (Safe)", keywords = "AutoActivate"))
	static void ComponentSetActiveSafe(UActorComponent* Component, bool bNewActive);
	
	/**
	 * Gets whether the component is active or not.
	 * If called during construction, will return AutoActivate.
	 */
	UFUNCTION(BlueprintPure, Category = "Components|Activation", meta = (DefaultToSelf = "Component", DisplayName = "Get Active (Safe)", keywords = "AutoActivate", ReturnDisplayName = "IsActive"))
	static bool ComponentGetActiveSafe(const UActorComponent* Component);

	/** Returns if this actor is currently running the User Construction Script */
	UFUNCTION(BlueprintPure, Category = "Actor", meta = (DefaultToSelf = "Actor", DisplayName = "Is Running Construction (Actor)", keywords = "Is RunningUserConstructionScript"))
	static UPARAM(DisplayName = "RunningConstruction") bool ActorIsRunningConstruction(const AActor* Actor);

	/** Returns whether an actor is in the process of beginning play */
	UFUNCTION(BlueprintPure, Category = "Actor", meta = (DefaultToSelf = "Actor", DisplayName = "Is Beginning Play (Actor)", keywords = "begun"))
	static void ActorIsBeginningPlay(const AActor* Actor, bool& BeginningPlay, bool& BeginningPlayFromLevelStreaming);

	/**
	* Returns whether an actor has had BeginPlay called on it (and not subsequently had EndPlay called)
	* This is False during BeginPlay
	*/
	UFUNCTION(BlueprintPure, Category = "Actor", meta = (DefaultToSelf = "Actor", DisplayName = "Has Begun Play (Actor)", keywords = "begin"))
	static UPARAM(DisplayName = "BegunPlay") bool ActorHasBegunPlay(const AActor* Actor);

	/**
	* Returns true once an actor has started its BeginPlay called on it (and not subsequently had EndPlay called)
	*/
	UFUNCTION(BlueprintPure, Category = "Actor", meta = (DefaultToSelf = "Actor", DisplayName = "Is in Play (Actor)", keywords = "begin, begun"))
	static UPARAM(DisplayName = "InPlay") bool ActorIsInPlay(const AActor* Actor);

	///* If this is being called from inside the UObject constructors. Not related the User Construction Script. */
	//UFUNCTION(BlueprintPure, Category = "Utility", meta = (DisplayName = "Is During Object Constructor", keywords = ""))
	//static bool IsDuringConstructor();

	/**
	 * Change the name shown in the world outliner.
	 */
	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (keywords = "rename, label", DevelopmentOnly))
	static void SetActorDisplayName(AActor* Actor, const FString DisplayName);

	/**
	 * Change the name of an object.
	 */
	UFUNCTION(BlueprintCallable, Category = "Object", meta = (keywords = "rename, label, set name"))
	static void RenameObject(UObject* Object, const FString Name);

	/**
	 * Sets root component to be the specified component.  NewRootComponent's owner should be this actor.
	 * @return true if successful
	 */
	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (DefaultToSelf = "Actor"))
	static UPARAM(DisplayName = "Success") bool SetRootComponent(AActor* Actor, USceneComponent* NewRootComponent);

	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "ActorClass"))
	static AActor* SpawnActorFromClass(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined, ESpawnActorScaleMethod TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot, AActor* Owner = nullptr, APawn* Instigator = nullptr);

	/**
	 * Generates the hash value for an element of this property.
	 *
	 * @param	Target		The value to get Hash of.
	 * @param	Hash		The Hash generated by the Target.
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Target", BlueprintThreadSafe), Category = "Utilities")
	static void GetHash(const int32& Target, int32& Hash);

	DECLARE_FUNCTION(execGetHash)
	{
		// Value Parameter (wildcard)
		Stack.StepCompiledIn<FProperty>(nullptr);
		FProperty* TargetProperty = CastField<FProperty>(Stack.MostRecentProperty);
		void* TargetAddress = Stack.MostRecentPropertyAddress;

		// Hash Parameter (int)
		PARAM_PASSED_BY_REF(HashParameter, FIntProperty, int);

		P_FINISH;
		P_NATIVE_BEGIN;
		// Hash is normally uint32, but blueprint doesn't support that, so here it is converted to int32.
		HashParameter = (int32)TargetProperty->GetValueTypeHash(TargetAddress);
		P_NATIVE_END;
	}

	/**
	 * Combines two hash values to get a third.
	 * Note - this function is not commutative.
	 *
	 * This function cannot change for backward compatibility reasons.
	 * You may want to choose HashCombineFast for a better in-memory hash combining function.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Hash Combine", BlueprintThreadSafe), Category = "Utilities")
	static int32 ExtendedHashCombine(const int32 A, const int32 B, const bool bOrderDependent = true);

	/**
 	* Combines two hash values to get a third.
 	* Note - this function is not commutative.
 	*
 	* WARNING!  This function is subject to change and should only be used for creating
 	*           combined hash values which don't leave the running process,
 	*           e.g. GetTypeHash() overloads.
 	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Hash Combine Fast", BlueprintThreadSafe), Category = "Utilities")
	static int32 ExtendedHashCombineFast(const int32 A, const int32 B, const bool bOrderDependent = true);

	/** Checks if this class implements a specific interface, works for both native and blueprint interfaces. */
	UFUNCTION(BlueprintPure, Category = "Utilities")
	static bool DoesClassImplementInterface(const UClass* Class, const TSubclassOf<UInterface> Interface);

	/**
	 * Auto destroy this component on completion, or destroy right now if the sound has finished.
	 *
	 * Does not destroy paused sounds.
	 */
	UFUNCTION(BlueprintCallable, Category = "Audio")
	static void DestroyAudioComponentWhenComplete(UAudioComponent* AudioComponent);

	/**
	 * Checks to see if Actor is one of Target's Owners.
	 */
	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (DisplayName = "Is Actor in Owner Chain", DefaultToSelf = "Target", CallableWithoutWorldContext))
	static UPARAM(DisplayName = "InChain") bool IsActorInActorOwnerChain(const AActor* Target, const AActor* Actor);

	/**
	* Checks to see if Actor is one of Target's Owners.
	*/
	UFUNCTION(BlueprintCallable, Category = "Components", meta = (DisplayName = "Is Actor in Owner Chain", DefaultToSelf = "Target", CallableWithoutWorldContext))
	static UPARAM(DisplayName = "InChain") bool IsActorInComponentOwnerChain(const UActorComponent* Target, const AActor* Actor);

	/**
	 * Gets all Owners of an Actor.
	 */
	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (DisplayName = "Get Owner Chain", DefaultToSelf = "Target", CallableWithoutWorldContext))
	static UPARAM(DisplayName = "OwnerChain") TArray<AActor*> GetActorOwnerChain(const AActor* Target);

	/**
	 * Gets all Owners of a Component.
	 */
	UFUNCTION(BlueprintCallable, Category = "Components", meta = (DisplayName = "Get Owner Chain", DefaultToSelf = "Target", CallableWithoutWorldContext))
	static UPARAM(DisplayName = "OwnerChain") TArray<AActor*> GetComponentOwnerChain(const UActorComponent* Target);

	/**
	 * Gets Actor Owner.
	 * Won't complain if Target is invalid.
	 */
	UFUNCTION(BlueprintPure, Category = "Actor", meta = (DisplayName = "Get Owner (Safe)", DefaultToSelf = "Target", CallableWithoutWorldContext))
	static UPARAM(DisplayName = "Owner") AActor* GetActorOwnerSafe(const AActor* Target);

	/**
	* Gets Component Owner.
	* Won't complain if Target is invalid.
	*/
	UFUNCTION(BlueprintPure, Category = "Components", meta = (DisplayName = "Get Owner (Safe)", DefaultToSelf = "Target", CallableWithoutWorldContext))
	static UPARAM(DisplayName = "Owner") AActor* GetComponentOwnerSafe(const UActorComponent* Target);

	/**
	 * Returns true if this is a replicated actor that was placed in the map.
	 */
	UFUNCTION(BlueprintPure, Category = "Actor", meta = (DefaultToSelf = "Target", CallableWithoutWorldContext))
	static bool IsNetStartupActor(const AActor* Target);

	/**
	 * Returns the target if it is an Actor or the Actor Owner if it is a Component.
	 */
	UFUNCTION(BlueprintPure, Category = "Object", meta = (DefaultToSelf = "Target", CallableWithoutWorldContext))
	static const AActor* AsActorOrOwner(const UObject* Target);


	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FTransformUpdatedDelegate, USceneComponent*, Component, const FTransform&, OldTransform, const FTransform&, NewTransform);
	/**
	 * Create binding to component's OnTransformUpdated delegate.
	 * Optionally disable elements of the transform's change detection.
	 * 
 	 * @param Target            Scene component to track for transform updates.
 	 * @param OnTransformUpdated Event to invoke when the component’s transform changes.
 	 * @param bLocationChange   If true, location changes will trigger the bound event.
 	 * @param bRotationChange   If true, rotation changes will trigger the bound event.
 	 * @param bScaleChange      If true, scale changes will trigger the bound event.
 	 * @param Tolerance         The minimum difference required to consider the transform changed.
 	 *
 	 * @return Binding handle which can be used to unbind the delegate.
	 */
	UFUNCTION(BlueprintCallable, Category = "Components", meta = (DefaultToSelf = "Target", CallableWithoutWorldContext, DisplayName = "Bind Event to On Transform Changed"))
	static UPARAM(DisplayName = "Handle") FDelegateHandleWrapper BindEventToOnTransformUpdated(USceneComponent* Target, UPARAM(DisplayName = "OnTransformChanged") FTransformUpdatedDelegate OnTransformUpdated, bool bLocationChange = true, bool bRotationChange = true, bool bScaleChange = true, double Tolerance = 1.e-4);

	/**
	 * Remove binding from component's OnTransformUpdated delegate.
	 */
	UFUNCTION(BlueprintCallable, Category = "Components", meta = (DefaultToSelf = "Target", CallableWithoutWorldContext))
	static void UnbindEventFromOnTransformUpdated(USceneComponent* Target, const FDelegateHandleWrapper& Handle);

	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FLocationUpdatedDelegate, USceneComponent*, Component, const FVector&, OldLocation, const FVector&, NewLocation);
	/**
	 * Create binding which fires whenever the component's location is changed.
	 */
	UFUNCTION(BlueprintCallable, Category = "Components", meta = (DefaultToSelf = "Target", CallableWithoutWorldContext, KeyWords = "Updated", DisplayName = "Bind Event to On Location Changed"))
	static FDelegateHandleWrapper BindEventToOnLocationChanged(USceneComponent* Target, FLocationUpdatedDelegate OnLocationChanged);

	/**
	 * Remove binding from component's OnTransformUpdated delegate.
	 */
	UFUNCTION(BlueprintCallable, Category = "Components", meta = (DefaultToSelf = "Target", CallableWithoutWorldContext))
	static void UnbindEventFromOnLocationUpdated(USceneComponent* Target, const FDelegateHandleWrapper& Handle);

	/** Returns true if this was ever bound to a delegate, but you need to check with the owning delegate to confirm it is still valid. */
	UFUNCTION(BlueprintCallable, Category = "DelegateHandle", meta = (DisplayName = "IsValid (DelegateHandle)", CallableWithoutWorldContext))
	static bool IsValid_DelegateHandleWrapper(UPARAM(Ref) FDelegateHandleWrapper& Handle);

	/** Clear handle to indicate it is no longer bound. */
	UFUNCTION(BlueprintCallable, Category = "DelegateHandle", meta = (DisplayName = "Reset (DelegateHandle)", CallableWithoutWorldContext, Keywords = "clear, unbind"))
	static void Reset_DelegateHandleWrapper(UPARAM(Ref) FDelegateHandleWrapper& Handle);

	/** Returns true if the values are equal (A == B). */
	UFUNCTION(BlueprintPure, Category = "DelegateHandle", meta = (DisplayName = "Equal (DelegateHandle)", CompactNodeTitle = "=="))
	static bool EqualEqual_DelegateHandleWrapper(FDelegateHandleWrapper A, FDelegateHandleWrapper B);

	/** Returns true if the values are not equal (A != B). */
	UFUNCTION(BlueprintPure, Category = "DelegateHandle", meta = (DisplayName = "Not Equal (DelegateHandle)", CompactNodeTitle = "!="))
	static bool NotEqual_DelegateHandleWrapper(FDelegateHandleWrapper A, FDelegateHandleWrapper B);
	/**
	 * Remove binding from component's OnTransformUpdated delegate.
	 */
	UFUNCTION(BlueprintCallable, Category = "Pawn", meta = (DefaultToSelf = "Pawn", CallableWithoutWorldContext))
	static void SetAutoPossessAI(APawn* Pawn, EAutoPossessAI AutoPossessAI);


	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (DevelopmentOnly))
	static void SetPreviewSkeletalMesh(UAnimationAsset* VertexAnimationProfileAsset, USkeletalMesh* PreviewMesh);

	/**
	 *
	 */
	UFUNCTION(BlueprintPure, Category = "Spline")
	static double GetDistanceAlongSplineAtTime(const class USplineComponent* Target, double Time, bool bUseConstantVelocity);

	/**
	 * Time will be adjusted by the stretching and squishing of the spline.
	 */
	UFUNCTION(BlueprintPure, Category = "Spline")
	static double GetTimeAlongSplineAtTime(const class USplineComponent* Target, double Time, bool bUseConstantVelocity);

	/**
	 * Time will be adjusted by the stretching and squishing of the spline.
	 */
	UFUNCTION(BlueprintPure, Category = "Spline")
	static double GetTimeAlongSplineAtSplinePoint(const class USplineComponent* Target, int Index, bool bUseConstantVelocity);


	////UFUNCTION(BlueprintPure, Category = "Component")
	////static UPARAM(DisplayName = "PointIsInside") bool IsPointInsideCollision(const class UPrimitiveComponent* Component, const FVector& Point);

	UFUNCTION(BlueprintPure, Category = "Component", meta = (Keywords = "within"))
	static UPARAM(DisplayName = "PointIsInside") bool IsPointInsideCapsule(const class UCapsuleComponent* Capsule, const FVector& Point);

	UFUNCTION(BlueprintPure, Category = "Component", meta = (Keywords = "within"))
	static UPARAM(DisplayName = "PointIsInside") bool IsPointInsideSphere(const class USphereComponent* Sphere, const FVector& Point);

	UFUNCTION(BlueprintPure, Category = "Component", meta = (Keywords = "within"))
	static UPARAM(DisplayName = "PointIsInside") bool IsPointInsideBox(const class UBoxComponent* Box, const FVector& Point);

	UFUNCTION(BlueprintPure, Category = "Components|Capsule")
	static UPARAM(DisplayName = "TopLocation") FVector GetCapsuleTopLocation(const UCapsuleComponent* Capsule);

	UFUNCTION(BlueprintPure, Category = "Components|Capsule")
	static UPARAM(DisplayName = "BottomLocation") FVector GetCapsuleBottomLocation(const UCapsuleComponent* Capsule);

	/**
	 * Get Object which implement the interface. Checks the actor and its components.
	 * Returns the first object it finds.
	 * By default will check the actor first.
	 *
	 * @param bPreferComponent Checks components first. If a component implements the interface it will be returned even if the actor implements the interface.
	 */
	UFUNCTION(BlueprintCallable, Category = "Interface")
	static void GetInterfaceImplementor(AActor* Actor, TSubclassOf<UInterface> Interface, const bool bPreferComponent, UObject*& Implementor);

	/**
	 * Get Objects which implement the interface. Checks the actor and its components.
	 * Returns the first object it finds.
	 * By default will check the actor first.
	 *
	 * @param bPreferComponent Checks components first. If a component implements the interface it will be returned even if the actor implements the interface.
	 */
	UFUNCTION(BlueprintCallable, Category = "Interface")
	static TArray<UObject*> GetInterfaceImplementors(AActor* Actor, TSubclassOf<UInterface> Interface);

	/**
	 * Get the transform of the player's viewport.
	 */
	UFUNCTION(BlueprintCallable, Category = "Viewport")
	static bool GetPlayerViewportTransform(const APlayerController* Player, FTransform& Transform);

	UFUNCTION(BlueprintCallable, Category = "Components|Timeline", meta = (DisplayName = "Set Duration", Duration = "1.0"))
	static void SetTimelineDuration(class UTimelineComponent* Timeline, double Duration);

	UFUNCTION(BlueprintPure, Category = "Components|Timeline", meta = (DisplayName = "Get Duration", ReturnDisplayName = "Duration"))
	static double GetTimelineDuration(class UTimelineComponent* Timeline);

	/**  **/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsInWater (MovementComponent)"), Category = "Components|Movement")
	static bool MovementComponent_IsInWater(class UMovementComponent* Target);

	UFUNCTION(BlueprintPure, Category = "Editor", meta = (WorldContext = "WorldContextObject", DevelopmentOnly))
	static UPARAM(DisplayName = "Location") FVector GetLevelEditingViewportLocation(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Editor", meta = (WorldContext = "WorldContextObject", DevelopmentOnly))
	static void SetLevelEditingViewportLocation(const UObject* WorldContextObject, const FVector Location);

	UFUNCTION(BlueprintPure, Category = "Editor", meta = (WorldContext = "WorldContextObject", DevelopmentOnly))
	static UPARAM(DisplayName = "Rotation") FRotator GetLevelEditingViewportRotation(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Editor", meta = (WorldContext = "WorldContextObject", DevelopmentOnly))
	static void SetLevelEditingViewportRotation(const UObject* WorldContextObject, const FRotator Rotation);

	/** Set which parts of the relative transform should be relative to parent, and which should be relative to world. Includes the option to have the component maintain its world transform. */
	UFUNCTION(BlueprintCallable, Category = "Transformation", meta = (DisplayName = "Set Absolute (Advanced)", DefaultToSelf = "Component"))
	static void SceneComponentSetAbsoluteAdvanced(USceneComponent* Component, const bool bNewAbsoluteLocation, const bool bNewAbsoluteRotation, const bool bNewAbsoluteScale, const bool bMaintainWorldTransform);
	
	
//	/**
//	 * Perform a latent action with a delay (specified in seconds). Calling again while it is counting down will reset the countdown to Duration if bRetriggerable is true.
//	 *
//	 * @param WorldContext		World context.
//	 * @param Duration 			length of delay (in seconds).
//	 * @param bRetriggerable	When True, recalling the event will restart the countdown.
//	 * @param LatentInfo 		The latent action.
//	*/
//	UFUNCTION(BlueprintCallable, Category = "Utilities|FlowControl", meta = (WorldContext = "WorldContextObject", Latent, LatentInfo = "LatentInfo", Duration = "0.2", ExpandEnumAsExecs = "Input,Output"))
//	static void DelaySeconds(const UObject* WorldContextObject, double Duration, bool bRetriggerable, EDelayInput Input, FLatentActionInfo LatentInfo, UPARAM(DisplayName = "")EDelayOutput& Output);

	UFUNCTION(BlueprintCallable, Category = "Editor", meta = (DevelopmentOnly))
	static void BrowseToAssets(const TArray<FAssetData>& Assets);

	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))
	static void EditorRequestPlaySession(bool bSimulate);

	/**
	 * Marks the transform as dirty - will be sent to the render thread at the end of the frame.
	 */
	UFUNCTION(BlueprintCallable, Category = "Component")
	static void MarkRenderTransformDirty(UActorComponent* Component);

	/**
	 * Mark the render state as dirty - will be sent to the render thread at the end of the frame.
	 */
	UFUNCTION(BlueprintCallable, Category = "Component")
	static void MarkRenderStateDirty(UActorComponent* Component);

	/**
	 *	If true, will keep geometry data CPU-accessible in cooked builds, rather than uploading to GPU memory and releasing it from CPU memory.
	 *	This is required if you wish to access StaticMesh geometry data on the CPU at runtime in cooked builds (e.g. to convert StaticMesh to ProceduralMeshComponent)
	 */
	UFUNCTION(BlueprintPure, Category = "Variables|StaticMesh")
	static bool GetAllowCPUAccess(const UStaticMesh* StaticMesh);

	/**
	 *	If true, will keep geometry data CPU-accessible in cooked builds, rather than uploading to GPU memory and releasing it from CPU memory.
	 *	This is required if you wish to access StaticMesh geometry data on the CPU at runtime in cooked builds (e.g. to convert StaticMesh to ProceduralMeshComponent)
	 */
	UFUNCTION(BlueprintCallable, Category = "Variables|StaticMesh", meta = (DevelopmentOnly))
	static void SetAllowCPUAccess(UStaticMesh* StaticMesh, const bool bAllowCPUAccess);

	UFUNCTION(BlueprintCallable, Category = "Math|Vector")
	static TArray<FVector> FlipVectors(const TArray<FVector>& Vectors);


	/**
	 * Returns an array of actors that overlap the given oriented box.
	 * @param WorldContext		World context
	 * @param BoxPos			Center of box.
	 * @param BoxExtent			Extents of box.
	 * @param BoxRotation		Orientation of box in world.
	 * @param Filter			Option to restrict results to only static or only dynamic.  For efficiency.
	 * @param ClassFilter		If set, will only return results of this class or subclasses of it.
	 * @param ActorsToIgnore	Ignore these actors in the list
	 * @param OutActors			Returned array of actors. Unsorted.
	 * @return					true if there was an overlap that passed the filters, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Collision", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Oriented Box Overlap Actors", DeterminesOutputType = "ActorClassFilter", DynamicOutputParam = "OutActors"))
	static bool OrientedBoxOverlapActors(const UObject* WorldContextObject, const FVector BoxPos, const FVector BoxExtent, const FRotator BoxRotation, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, TSubclassOf<AActor> ActorClassFilter, const TArray<AActor*>& ActorsToIgnore, TArray<AActor*>& OutActors
	);

	/**
	 * Returns an array of components that overlap the given axis-aligned box.
	 * @param WorldContext		World context
	 * @param BoxPos			Center of box.
	 * @param BoxExtent			Extents of box.
	 * @param BoxRotation		Orientation of box in world.
	 * @param Filter			Option to restrict results to only static or only dynamic.  For efficiency.
	 * @param ClassFilter		If set, will only return results of this class or subclasses of it.
	 * @param ActorsToIgnore		Ignore these actors in the list
	 * @param OutActors			Returned array of actors. Unsorted.
	 * @return					true if there was an overlap that passed the filters, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Collision", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "Oriented Box Overlap Components", DeterminesOutputType = "ComponentClassFilter", DynamicOutputParam = "OutComponents"))
	static bool OrientedBoxOverlapComponents(const UObject* WorldContextObject, const FVector BoxPos, const FVector BoxExtent, const FRotator BoxRotation, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, TSubclassOf<UActorComponent> ComponentClassFilter, const TArray<AActor*>& ActorsToIgnore, TArray<UPrimitiveComponent*>& OutComponents);

	/**
	* Returns true if the sphere overlaps the collision of the component.
	* Component must have simple collision to be queried for closest point.
	*
	* @param Point				World 3D vector
	* @param OutPointOnBody		Point on the surface of collision closest to Point
	* @param BoneName			If a SkeletalMeshComponent, name of body to set center of mass of. 'None' indicates root body.
	*
	* @return		True if the sphere overlaps the collision.
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision") //, meta = (UnsafeDuringActorConstruction = "true"))
	static bool SphereOverlapComponentCollision(const UPrimitiveComponent* Component, const FVector& Point, const float Radius, FName BoneName, UPARAM(DisplayName = "ClosestPoint") FVector& OutClosestPoint, UPARAM(DisplayName = "Distance") double& OutDistance);

	static bool GetClosestPointOnBodySetup(UBodySetup* BodySetup, const FTransform& BodyTransform, const FVector& Point, FVector& ClosestPoint, double& DistanceSquared);

	/**
	* Returns the distance and closest point on/in the component's Simple Collision.
	* Component must have simple collision to be queried for closest point.
	* This will work even if collision is disabled, unlike in UPrimitiveComponent::GetClosestPointOnCollision.
	*
	* @param Component					Component to check point against.
	* @param BoneName					If a SkeletalMeshComponent: name of body to set center of mass of. 'None' indicates root body.
	* @param Point						Location in world space to check.
	* @param OutPointOnCollision		Closest location on/in the collision from Point.
	* @param Distance					Distance from point to the closest location.
	*
	* @return		Success if true: it is either not convex or inside of the point
	*				If false: this primitive does not have collsion
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision")
	static bool GetClosestPointOnCollision(UPrimitiveComponent* Component, const FName BoneName, const FVector& Point, UPARAM(DisplayName = "ClosestPoint") FVector& OutClosestPoint, UPARAM(DisplayName = "Distance") double& OutDistance);

	/**
	 * Calculates the closest point on/in the Component's Oriented Bounding Box to a given point.
	 *
	 * @param Component The Component's bounds to check.
	 * @param Point Location in world space to check.
	 * @param OutPointOnBounds Closest location on/in the collision from Point.
	 * @param OutDistance Distance from the given Point to OutPointOnBounds.
	 *
	 * @return True if a valid closest point was found. False if the Component was null or had no bounds.
	 */
	UFUNCTION(BlueprintCallable, Category = "Collision")
	static bool GetClosestPointOnComponentBounds(UPrimitiveComponent* Component, const FVector& Point, UPARAM(DisplayName = "ClosestPoint") FVector& OutClosestPoint, UPARAM(DisplayName = "Distance") double& OutDistance);

	/**
	 * Gets the segments of path where points overlap a component's collision as capsule.
	 * @param Path The path to check for overlapping segments.
	 * @param CapsuleRadius The radius of the capsule.
	 * @param CapsuleHalfHeight The half height of the capsule.
	 * @param CapsuleOrientation The orientation of the capsule.
	 * @param Component The component to check for overlapping segments.
	 * @return The contiguous segments of the path which overlap the component's collision.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Segments Overlaping Component"), Category = "Math")
	static UPARAM(DisplayName = "Paths") TArray<FVectorArray> GetSegmentsOverlapingComponent(const TArray<FVector>& Path, const double CapsuleRadius, const double CapsuleHalfHeight, const FRotator CapsuleOrientation, UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "GameplayStatics", meta = (Keywords = "MakeSureMapNameIsValid"))
	static bool IsLevelNameValid(const FName LevelName);

	/** Get Character Arrow Component **/
	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "Target", DevelopmentOnly), Category = "Character")
	static class UArrowComponent* GetCharacterArrow(ACharacter* Target);

	/**
	 * Sets the component sprite
	 * Issue: Does not hide the existing root sprite.
	**/
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", DevelopmentOnly), Category = "Actor")
	static void SetComponentSprite(USceneComponent* SceneComponent, UTexture2D* SpriteTexture);

	/**
	 * Sets the component sprite
	 * Issue: Does not hide the existing sprite.
	**/
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", DevelopmentOnly), Category = "Actor")
	static UBillboardComponent* SetActorRootSprite(AActor* Target, UTexture2D* SpriteTexture);

	/** Transient Objects are not saved. **/
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target"), Category = "Object")
	static void SetTransient(UObject* Target, const bool bTransient = true);

	/** Transient Objects are not saved. **/
	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "Target"), Category = "Object")
	static bool GetTransient(const UObject* Target);

	/** Set whether this actor is editor-only. Use with care, as if this actor is referenced by anything else that reference will be NULL in cooked builds. **/
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target"), Category = "Object")
	static void SetEditorOnlyActor(AActor* Target, const bool bIsEditorOnlyActor = true);

	/** Get whether this actor is editor-only. Use with care, as if this actor is referenced by anything else that reference will be NULL in cooked builds. **/
	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "Target"), Category = "Object")
	static bool IsEditorOnlyActor(const AActor* Target);

	/** 
	 * Sets character's jump velocity based on the desired JumpHeight.
	 * Gravity is accounted for, giving the character a consistent jump apex.
	 * If Gravity is zero, then JumpZVelocity will not be changed.
	 * 
	 * @param CharacterMovement Character Movement Component.
	 * @param JumpHeight How high the character will move vertically.
	 * @return True if Gravity is non-zero. JumpZVelocity remains unchanged.
	 **/
	UFUNCTION(BlueprintCallable, Category = "CharacterMovement")
	static bool SetJumpHeight(class UCharacterMovementComponent* CharacterMovement, const float JumpHeight);

	//UFUNCTION(BlueprintCallable, Category = "Spline")
	//static void SetSplineComponentPointInterpMode(class USplineComponent* SplineComponent, int32 PointIndex, TEnumAsByte<EInterpCurveMode> Mode, bool bUpdateSpline);


	/** 
	 * Calculates Character origin location which would put the character's base at the given BaseLocation.
	 **/
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", keywords = "feet, convert"), Category = "Character")
	static FVector GetCharacterOriginFromBaseLocation(const ACharacter* Target, const FVector BaseLocation);

	/** 
	 * Gets location at the base of the character capsule.
	 **/
	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "Target", keywords = "feet, convert"), Category = "Character")
	static UPARAM(DisplayName = "BaseLocation") FVector GetCharacterBaseLocation(const ACharacter* Target);

	/**
	 * Sets character capsule bottom to the specified location.
	 **/
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", keywords = "feet"), Category = "Character")
	static bool SetCharacterBaseLocation(ACharacter* Target, const FVector BaseLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);

	/**
	 * Sets character capsule bottom to the specified location and rotation.
	 **/
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", keywords = "feet"), Category = "Character")
	static bool SetCharacterBaseLocationAndRotation(ACharacter* Target, const FVector BaseLocation, FRotator BaseRotation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);

	/**
	 * Finds all actors in the world with the given GUIDs.
	 **/
	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", HidePin = "WorldContextObject", DevelopmentOnly))
	static TArray<AActor*> FindActorsByFileNames(const UObject* WorldContextObject, const TArray<FString>& FileNames);

	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh", meta = (DisplayName = "Set UseComplexAsSimpleCollision (ProceduralMeshComponent)"))
	static void ProceduralMesh_SetUseComplexAsSimpleCollision(class UProceduralMeshComponent* Target, bool bUseComplexAsSimpleCollision = true);

	/**
	 * Registers an object to keep alive as long as the current game instance is alive.
	 * Ignores Actors and Actor Components.
	 **/
	UFUNCTION(BlueprintCallable, Category = "Object")
	static void RegisterReferencedObject(UObject* WorldContext, UObject* Object);

	/**
	 * Unregisters a referenced object, this will allow it to be GC'd if not referenced anywhere else.
	 * Ignores Actors and Actor Components.
	 **/
	UFUNCTION(BlueprintCallable, Category = "Object")
	static void UnregisterReferencedObject(UObject* WorldContext, UObject* Object);

	/**
	 * Opens the specified directory in the system's file explorer.
	 *
	 * @param DirectoryPath The absolute path of the directory to open.
	 * @return true if the directory exists and was successfully opened; false otherwise.
	 **/
	UFUNCTION(BlueprintCallable, Category = "Utilities|Paths", meta = (KeyWords = "explore, folder"))
	static bool OpenDirectoryInFileSystem(const FString& DirectoryPath);

	//static int GetNumberOfShadersBeingCompiled() {return FShaderCompilingManager::GetNumPendingJobs();}

	UFUNCTION(BlueprintCallable, Category = "Utilities|Paths", meta = (KeyWords = "explore, folder", DevelopmentOnly))
	static void ModifyAndCompileBlueprintClass(UClass* Class);

	/**
	 * Get statistics about the shader compiling manager.
	 * 
	 * @param TotalShadersCompiled Total number of shaders that have been compiled.
	 * @param LocalWorkersCount Number of curernt local shader compiling workers.
	 * @param PendingJobsCount Number of pending shader compilation jobs.
	 * @param OutstandingJobsCount Number of outstanding shader compilation jobs.
	 * @param ExternalJobsCount Number of jobs currently being compiled. This includes CompileQueue and any jobs that have been assigned to workers but aren't complete yet.
	 * @param RemainingJobsCount Number of outstanding compile jobs plus External Jobs.
	 * @param bHasShaderJobs true if we have shader jobs in any state. Shader jobs are removed when they are applied to the GameThreadShaderMap.
	 * @param bIsCompiling true if async compiling is happening.
	 * 
	 * @return true if the ShaderCompilingManager existed.
	 **/
	UFUNCTION(BlueprintCallable, Category = "Shader Compilation", meta = (ReturnDisplayName = "Success"))
	static bool GetShaderCompilingStats(int32& TotalShadersCompiled, int32& LocalWorkersCount, int32& PendingJobsCount, int32& OutstandingJobsCount, int32& ExternalJobsCount, int32& RemainingJobsCount, bool& bHasShaderJobs, bool& bIsCompiling);

	/**
	 * Retrieves the value of a Static Switch (bool) parameter only from the specified Material Instance.
	 * Does NOT check parent materials or the base material.
	 *
	 * @param MaterialInstance The Material Instance to query.
	 * @param ParameterName Name of the Static Switch Parameter.
	 * @param bValue Output parameter that receives the value of the parameter if found.
	 * @return True if the parameter exists on this instance, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Rendering|Material", meta = (DisplayName = "Get StaticSwitch (bool) Parameter Override Value", ReturnName = "Found"))
	static bool GetStaticSwitchBoolOverride(const UMaterialInstance* MaterialInstance, const FName ParameterName, bool& bValue);

	/**
	 * Retrieves the fully resolved value of a Static Switch (bool) parameter from a Material or Material Instance.
	 * Traverses parent chain and falls back to base material if necessary.
	 *
	 * @param MaterialInterface The Material or Material Instance to query.
	 * @param ParameterName Name of the Static Switch Parameter.
	 * @param bValue Output parameter that receives the value of the parameter if found.
	 * @return True if the parameter exists anywhere in the hierarchy, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Rendering|Material", meta = (DisplayName = "Get StaticSwitch (bool) Parameter Value", ReturnName = "Found"))
	static bool GetStaticSwitchBoolValue(const UMaterialInterface* MaterialInterface, const FName ParameterName, bool& bValue);

	/** Plays an in-world camera shake that affects all nearby local players, with distance-based attenuation. Does not replicate.
	 * @param WorldContextObject - Object that we can obtain a world context from
	 * @param Shake - Camera shake asset to use
	 * @param Epicenter - location to place the effect in world space
	 * @param InnerRadius - Cameras inside this radius are ignored
	 * @param OuterRadius - Cameras outside of InnerRadius and inside this are effected
	 * @param Falloff - Affects falloff of effect as it nears OuterRadius
	 * @param bOrientShakeTowardsEpicenter - Changes the rotation of shake to point towards epicenter instead of forward
	 * @param Strength - Scale the intensity of the shake.
	 */
	UFUNCTION(BlueprintCallable, Category="Camera", meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction = "true", DisplayName = "Play World Camera Shake (Advanced)"))
	static void PlayWorldCameraShakeAdvanced(const UObject* WorldContextObject, TSubclassOf<class UCameraShakeBase> Shake, FVector Epicenter, float InnerRadius, float OuterRadius, float Falloff = 1.f, bool bOrientShakeTowardsEpicenter = false, float Strength = 1.f);


	/**
	 * Predict where an actor will be after a given amount of time, sweeping collision along the path.
	 * Uses the actor's actual component collision settings for accurate prediction.
	 * Automatically uses projectile motion for falling characters or physics objects with gravity.
	 * 
	 * @param WorldContextObject    World context
	 * @param Actor                 The actor to predict
	 * @param PredictionTime        How far into the future to predict (in seconds)
	 * @param bTracePath            If true, fill PathPositions array with intermediate points
	 * @param ClampVelocity         If > 0, limits the maximum initial velocity used for prediction
	 * @param ActorsToIgnore        Actors to ignore during the sweep
	 * @param DrawDebugType         Debug visualization option
	 * @param DrawDebugTime         Duration to display debug visualization
	 * @param SimFrequency          Simulation steps per second (for ungrounded/projectile motion, higher = more accurate)
	 * @param OutResult             Prediction result containing location, hit info, and path
	 * @return                      True if the sweep resulted in a blocking hit
	 */
	UFUNCTION(BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "DrawDebugTime, DrawDebugType, SimFrequency, MaxSimTime, OverrideGravityZ", TraceChannel = ECC_WorldDynamic, bTracePath = true, ClampVelocity = 0))
    static bool PredictActorPath(const UObject* WorldContextObject, AActor* Actor, float PredictionTime, FPredictActorPathResult& OutResult, bool bTracePath, float ClampInitialVelocity, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, float DrawDebugTime = 2.0f, float SimFrequency = 15.0f);
};
