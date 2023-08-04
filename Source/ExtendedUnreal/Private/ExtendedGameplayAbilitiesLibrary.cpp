// Copyright 2023 Dream Seed LLC.


#include "ExtendedGameplayAbilitiesLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffect.h"
#include "AbilitySystemLog.h"
#include "Abilities/Tasks/AbilityTask.h"


void UExtendedGameplayAbilitiesLibrary::SetNumericAttributeBaseOnAbilitySystem(UAbilitySystemComponent* AbilitySystem, const FGameplayAttribute Attribute, float NewBaseValue)
{
	if (IsValid(AbilitySystem))
	{
		AbilitySystem->SetNumericAttributeBase(Attribute, NewBaseValue);
	}
}

void UExtendedGameplayAbilitiesLibrary::SetActorNumericAttributeBaseOnActor(const AActor* Actor, const FGameplayAttribute Attribute, float NewBaseValue)
{
	if (IsValid(Actor))
	{
		UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor);
		if (IsValid(AbilitySystem))
		{
			AbilitySystem->SetNumericAttributeBase(Attribute, NewBaseValue);
		}
	}
}

TMap<FGameplayTag, float> UExtendedGameplayAbilitiesLibrary::GetSetByCallerTagMagnitudesFromGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& SpecHandle)
{
	if (FGameplayEffectSpec* Spec = SpecHandle.Data.Get(); Spec)
	{
		return Spec->SetByCallerTagMagnitudes;
	}
	else
	{
		ABILITY_LOG(Warning, TEXT("UExtendedGameplayAbilitiesLibrary::GetSetByCallerTagMagnitudesFromGameplayEffectSpec called with invalid SpecHandle"));
		return TMap<FGameplayTag, float>();
	}
}

TMap<FName, float> UExtendedGameplayAbilitiesLibrary::GetSetByCallerNameMagnitudesFromGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& SpecHandle)
{
	if (FGameplayEffectSpec* Spec = SpecHandle.Data.Get(); Spec)
	{
		return Spec->SetByCallerNameMagnitudes;
	}
	else
	{
		ABILITY_LOG(Warning, TEXT("UExtendedGameplayAbilitiesLibrary::GetSetByCallerNameMagnitudesFromGameplayEffectSpec called with invalid SpecHandle"));
		return TMap<FName, float>();
	}
}

TMap<FGameplayTag, float> UExtendedGameplayAbilitiesLibrary::GetSetByCallerTagMagnitudesFromGameplayEffectSpec(const FGameplayEffectSpec& Spec)
{
	return Spec.SetByCallerTagMagnitudes;
}

TMap<FName, float> UExtendedGameplayAbilitiesLibrary::GetSetByCallerNameMagnitudesFromGameplayEffectSpec(const FGameplayEffectSpec& Spec)
{
	return Spec.SetByCallerNameMagnitudes;
}

TArray<FGameplayTag> UExtendedGameplayAbilitiesLibrary::GetGameplayEffectClassSetByCallerTags(const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	TArray<FGameplayTag> SetByCallerTags;

	if (!GameplayEffectClass)
		return SetByCallerTags;

	UGameplayEffect* GameplayEffect = Cast<UGameplayEffect>(GameplayEffectClass->GetDefaultObject());
	for (FGameplayModifierInfo& Modifier : GameplayEffect->Modifiers)
	{
		// Use code-reflection to get protected SetByCallerMagnitude variable:
		// SetByCallerTags.Add(Modifier.ModifierMagnitude.SetByCallerMagnitude.DataTag);
		if (FProperty* Property = FGameplayEffectModifierMagnitude::StaticStruct()->FindPropertyByName(TEXT("SetByCallerMagnitude")); Property)
		{
			FSetByCallerFloat SetByCallerMagnitude;
			Property->GetValue_InContainer(&Modifier.ModifierMagnitude, &SetByCallerMagnitude);
			SetByCallerTags.Add(SetByCallerMagnitude.DataTag);
		}
	}

	return SetByCallerTags;
}

bool UExtendedGameplayAbilitiesLibrary::HasAbility(const AActor* Actor, const TSubclassOf<UGameplayAbility>& Ability)
{
	if(IsValid(Actor))
	{
		if (UAbilitySystemComponent* Component = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor); IsValid(Component))
		{
			return Component->FindAbilitySpecFromClass(Ability) != nullptr;
		}
	}

	return false;
}
