// Copyright 2023 Dream Seed LLC.

#pragma once

#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "ExtendedGameplayAbilitiesLibrary.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
struct FGameplayAbilitySpec;
struct FGameplayEffectSpec;
struct FGameplayTag;


/**
 * 
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedGameplayAbilitiesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/** Sets the base value of an attribute. Existing active modifiers are NOT cleared and will act upon the new base value. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Attributes", meta = (DisplayName = "Set Float Attribute Base (Ability System)"))
	static void SetNumericAttributeBaseOnAbilitySystem(UAbilitySystemComponent* AbilitySystem, const FGameplayAttribute Attribute, float NewBaseValue);
	
	/** Sets the base value of an attribute. Existing active modifiers are NOT cleared and will act upon the new base value. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Attributes", meta = (DisplayName = "Set Float Attribute Base (Actor)"))
	static void SetActorNumericAttributeBaseOnActor(const AActor* Actor, const FGameplayAttribute Attribute, float NewBaseValue);

	/** Sets the base value of an attribute. Existing active modifiers are NOT cleared and will act upon the new base value. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect", meta = (DisplayName = "Get SetByCaller Tag Magnitudes"))
	static TMap<FGameplayTag, float> GetSetByCallerTagMagnitudesFromGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& SpecHandle);

	/** Sets the base value of an attribute. Existing active modifiers are NOT cleared and will act upon the new base value. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect", meta = (DisplayName = "Get SetByCaller Name Magnitudes"))
	static TMap<FName, float> GetSetByCallerNameMagnitudesFromGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& SpecHandle);

	/** Sets the base value of an attribute. Existing active modifiers are NOT cleared and will act upon the new base value. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect", meta = (DisplayName = "Get SetByCaller Tag Magnitudes"))
	static TMap<FGameplayTag, float> GetSetByCallerTagMagnitudesFromGameplayEffectSpec(const FGameplayEffectSpec& Spec);

	/** Sets the base value of an attribute. Existing active modifiers are NOT cleared and will act upon the new base value. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect", meta = (DisplayName = "Get SetByCaller Name Magnitudes"))
	static TMap<FName, float> GetSetByCallerNameMagnitudesFromGameplayEffectSpec(const FGameplayEffectSpec& Spec);

	/** Returns true if the Actor has the given Ability */
	UFUNCTION(BlueprintPure, Category = "GameplayEffect", meta = (DisplayName = "Get GameplayEffect Class SetByCaller Tag"))
	static TArray<FGameplayTag> GetGameplayEffectClassSetByCallerTags(const TSubclassOf<UGameplayEffect> GameplayEffectClass);

	/** Returns true if the Actor has the given Ability */
	UFUNCTION(BlueprintPure, Category = "Ability", meta = (DisplayName = "Has Ability"))
	static bool HasAbility(const AActor* Actor, const TSubclassOf<UGameplayAbility>& Ability);

};
