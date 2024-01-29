// Copyright 2023 Dream Seed LLC.

#pragma once

#include "Enums/WorldType.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"


#include "ExtendedUnrealLibrary.generated.h"

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
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", Class = "Actor", DeterminesOutputType = "Class", Category = "Actor", keywords = "find"))
	static UPARAM(DisplayName = "AttachedActors") TArray<AActor*> GetAttachedActorsOfClass(const AActor* Target, TSubclassOf<AActor> Class, bool bRecursivelyIncludeAttachedActors);

	static void GetAttachedActorsOfClass_InternalAppend(const AActor* Target, TSubclassOf<AActor> Class, TArray<AActor*>& AttachedActors, bool bRecursivelyIncludeAttachedActors);

	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Target", Class = "Actor", DeterminesOutputType = "Class", Category = "Actor", keywords = "find"))
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
	static void SetActorDisplayName(AActor* Actor, FString DisplayName);

	/**
	 * Generates the hash value for an element of this property.
	 *
	 * @param	Target		The value to get Hash of.
	 * @param	Hash		The Hash generated by the Target.
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (DisplayName = "Get Hash", CustomStructureParam = "Target", BlueprintThreadSafe), Category = "Utilities")
	static void GetHash(const int32& Target, int32& Hash);

	DECLARE_FUNCTION(execGetHash)
	{
		// Value Parameter (wildcard)
		Stack.StepCompiledIn<FProperty>(nullptr);
		FProperty* TargetProperty = CastField<FProperty>(Stack.MostRecentProperty);
		void* TargetAddress = Stack.MostRecentPropertyAddress;

		// Hash Parameter (int)
		//PARAM_PASSED_BY_REF(HashParameter, FUInt32Property, uint32);
		PARAM_PASSED_BY_REF(HashParameter, FIntProperty, int);

		P_FINISH;
		P_NATIVE_BEGIN;
		// Hash is normally uint32, but blueprint doesn't support that, so here it is converted to int32.
		HashParameter = (int32)TargetProperty->GetValueTypeHash(TargetAddress);
		P_NATIVE_END;
	}

	UFUNCTION(BlueprintCallable, Category = "Rendering|Material")
	static UPARAM(DisplayName = "Data") TArray<float> GetCustomPrimitiveData(const UPrimitiveComponent* Target);

	UFUNCTION(BlueprintCallable, Category = "Rendering|Material")
	static UPARAM(DisplayName = "Data") float GetCustomPrimitiveDataFloat(const UPrimitiveComponent* Target, int32 DataIndex);

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

};
