// Copyright 2023 Dream Seed LLC.


#include "ExtendedGameplayTagLibrary.h"

#include "GameplayTagsManager.h"

void UExtendedGameplayTagLibrary::AddGameplayTagContainers(UPARAM(ref) FGameplayTagContainer& TagContainer, const FGameplayTagContainer& OtherTagContainer)
{
	TArray<FGameplayTag> AddTags;
	OtherTagContainer.GetGameplayTagArray(AddTags);

	for (FGameplayTag AddTag : AddTags)
	{
		TagContainer.AddTag(AddTag);
	}
}


FString UExtendedGameplayTagLibrary::Conv_GameplayTagToString(FGameplayTag GameplayTag)
{
	return GameplayTag.ToString();
}

FName UExtendedGameplayTagLibrary::Conv_GameplayTagToName(FGameplayTag GameplayTag)
{
	return GameplayTag.GetTagName();
}

FGameplayTag UExtendedGameplayTagLibrary::Conv_NameToGameplayTag(FName Name)
{
	if (UGameplayTagsManager* Manager = UGameplayTagsManager::GetIfAllocated())
	{
		return Manager->RequestGameplayTag(Name, false);
	}

	return FGameplayTag();
}

FGameplayTagContainer UExtendedGameplayTagLibrary::Conv_StringsToGameplayTagContainer(TArray<FString> Strings)
{
	FGameplayTagContainer GameplayTagContainer;
	if (UGameplayTagsManager* Manager = UGameplayTagsManager::GetIfAllocated())
	{
		Manager->RequestGameplayTagContainer(Strings, GameplayTagContainer, false);
	}

	return GameplayTagContainer;
}

FGameplayTagContainer UExtendedGameplayTagLibrary::Conv_StringToGameplayTagContainer(FString String)
{
	TArray<FString> Strings;
	String.ParseIntoArray(Strings, TEXT(","));

	FGameplayTagContainer GameplayTagContainer;
	if (UGameplayTagsManager* Manager = UGameplayTagsManager::GetIfAllocated())
	{
		Manager->RequestGameplayTagContainer(Strings, GameplayTagContainer, false);
	}

	return GameplayTagContainer;
}

TArray<FString> UExtendedGameplayTagLibrary::Conv_GameplayTagContainerToStrings(FGameplayTagContainer GameplayTagContainer)
{
	TArray<FString> Strings;
	GameplayTagContainer.ToStringSimple().ParseIntoArray(Strings, TEXT(","));
	return Strings;
}

FString UExtendedGameplayTagLibrary::Conv_GameplayTagContainerToString(FGameplayTagContainer GameplayTagContainer)
{
	return GameplayTagContainer.ToStringSimple();
}

//void UExtendedGameplayTagLibrary::MakeGameplayTagContainerFromStrings(const TArray<FString>& Strings, FGameplayTagContainer& GameplayTagContainer)
//{
//	if (UGameplayTagsManager* Manager = UGameplayTagsManager::GetIfAllocated())
//	{
//		Manager->RequestGameplayTagContainer(Strings, GameplayTagContainer, false);
//	}
//}
