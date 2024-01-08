// Copyright 2023 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"


#include "ExtendedGameplayTagLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedGameplayTagLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 * Adds tags from OtherTagContainer to the passed in TagContainer.
	 *
	 * @param TagContainer		The container that will be appended too.
	 * @param OtherTagContainer	The tags to add to the container.
	 */
	UFUNCTION(BlueprintCallable, Category = "GameplayTags", meta = (BlueprintThreadSafe))
	static void AddGameplayTagContainers(UPARAM(ref) FGameplayTagContainer& TagContainer, const FGameplayTagContainer& OtherTagContainer);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (GameplayTag)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameplayTags")
	static FString Conv_GameplayTagToString(FGameplayTag GameplayTag);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Name (GameplayTag)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameplayTags")
	static FName Conv_GameplayTagToName(FGameplayTag GameplayTag);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To GameplayTag (Name)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameplayTags")
	static FGameplayTag Conv_NameToGameplayTag(FName Name);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To GameplayTagContainer (Strings)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameplayTags")
	static FGameplayTagContainer Conv_StringsToGameplayTagContainer(TArray<FString> Strings);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To GameplayTagContainer (String)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameplayTags")
	static FGameplayTagContainer Conv_StringToGameplayTagContainer(FString String);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Strings (GameplayTagContainer)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameplayTags")
	static TArray<FString> Conv_GameplayTagContainerToStrings(FGameplayTagContainer GameplayTagContainer);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (GameplayTagContainer)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameplayTags")
	static FString Conv_GameplayTagContainerToString(FGameplayTagContainer GameplayTagContainer);

	//UFUNCTION(BlueprintPure, meta = (DisplayName = "To GameplayTagContainer (Strings)"), Category = "GameplayTags")
	//static void MakeGameplayTagContainerFromStrings(const TArray<FString>& Strings, FGameplayTagContainer& GameplayTagContainer);
	
};
