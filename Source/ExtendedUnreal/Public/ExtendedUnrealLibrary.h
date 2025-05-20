// Copyright 2025 Dream Seed LLC.

#pragma once

#include "Enums/WorldType.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"


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


DECLARE_DYNAMIC_DELEGATE_TwoParams(FTransformUpdatedDelegate, USceneComponent*, Component, const FTransform&, NewTransform);

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

	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (WorldContext = "WorldContextObject"))
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
	static int32 ExtendedHashCombine(const int32 A, const int32 B);

	/**
 	* Combines two hash values to get a third.
 	* Note - this function is not commutative.
 	*
 	* WARNING!  This function is subject to change and should only be used for creating
 	*           combined hash values which don't leave the running process,
 	*           e.g. GetTypeHash() overloads.
 	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Hash Combine Fast", BlueprintThreadSafe), Category = "Utilities")
	static int32 ExtendedHashCombineFast(const int32 A, const int32 B);

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

	/**
	 * Create binding to component's OnTransformUpdated delegate.
	 */
	UFUNCTION(BlueprintCallable, Category = "Components", meta = (DefaultToSelf = "Target", CallableWithoutWorldContext))
	static UPARAM(DisplayName = "Handle") FDelegateHandleWrapper BindEventToOnTransformUpdated(USceneComponent* Target, FTransformUpdatedDelegate OnTransformUpdated);

	/**
	 * Remove binding from component's OnTransformUpdated delegate.
	 */
	UFUNCTION(BlueprintCallable, Category = "Components", meta = (DefaultToSelf = "Target", CallableWithoutWorldContext))
	static void UnbindEventFromOnTransformUpdated(USceneComponent* Target, const FDelegateHandleWrapper& Handle);

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
	static void SetPreviewSkeletalMesh(UAnimationAsset* AnimationAsset, USkeletalMesh* PreviewMesh);

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

	UFUNCTION(BlueprintCallable)
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
	static bool SphereOverlapComponentCollision(const UPrimitiveComponent * Component, const FVector& Point, const float Radius, FName BoneName, FVector& OutPointOnBody, float& Distance);

	/**
	* Returns the distance and closest point to the collision surface.
	* Component must have simple collision to be queried for closest point.
	* This will work even if collision is disabled, unlike in UPrimitiveComponent::GetClosestPointOnCollision.
	*
	* @param Component					Component to check point against.
	* @param BoneName					If a SkeletalMeshComponent, name of body to set center of mass of. 'None' indicates root body.
	* @param Point						World 3D vector.
	* @param OutPointOnCollision		Point on the surface of collision closest to Point.
	* @param Distance					Distance from point to the closest location.
	*
	* @return		Success if true: it is either not convex or inside of the point
	*				If false: this primitive does not have collsion
	*/
	UFUNCTION(BlueprintCallable, Category = "Collision", meta=(UnsafeDuringActorConstruction="true"))
	static bool GetClosestPointOnCollision(UPrimitiveComponent* Component, const FName BoneName, const FVector& Point, FVector& OutPointOnCollision, double& Distance);

	static bool GetClosestPointOnBodySetup(UBodySetup* BodySetup, const FTransform& BodyTransform, const FVector& Point, FVector& ClosestPoint, double& DistanceSquared);
	
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
	static FVector GetCharacterOriginFromBaseLocation(ACharacter* Target, const FVector BaseLocation);

	/** 
	 * Gets location at the base of the character capsule.
	 **/
	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "Target", keywords = "feet, convert"), Category = "Character")
	static UPARAM(DisplayName = "BaseLocation") FVector GetCharacterBaseLocation(const ACharacter* Target);

	/**
	 * Finds all actors in the world with the given GUIDs.
	 **/
	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", HidePin = "WorldContextObject", DevelopmentOnly))
	static TArray<AActor*> FindActorsByFileNames(const UObject* WorldContextObject, const TArray<FString>& FileNames);

	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh", meta = (DisplayName = "Set UseComplexAsSimpleCollision (ProceduralMeshComponent)"))
	static void ProceduralMesh_SetUseComplexAsSimpleCollision(class UProceduralMeshComponent* Target, bool bUseComplexAsSimpleCollision = true);

};
