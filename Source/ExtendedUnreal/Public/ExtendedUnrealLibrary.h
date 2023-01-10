// Copyright 2022 Dream Seed LLC.

#pragma once

#include "Enums/WorldType.h"
#include "GameplayTagContainer.h"


#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExtendedUnrealLibrary.generated.h"

UCLASS()
class UExtendedUnrealLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:


	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "World")
	static float GetWorldGravity(const UObject* WorldContextObject);


	UFUNCTION(BlueprintCallable, Category = "Editor")
	static void ExploreFolders();


	UFUNCTION(BlueprintPure, Category = "World", meta = (DefaultToSelf = "WorldContextObject"))
	static WorldType GetWorldType(UObject* WorldContextObject);

	static WorldType WorldTypeToBlueprintCompatible(EWorldType::Type WorldType);


	UFUNCTION(BlueprintPure, Category = "Widget|Brush", meta = (Keywords = "get"))
	static void MakeBrushFromAppStyle(FName Name, FSlateBrush& Brush);

	UFUNCTION(BlueprintPure, Category = "Widget|Brush")
	static void MakeBrushFromSVGPath(const FString SVGPath, FSlateBrush& Brush, const FVector2D& InImageSize = FVector2D(16.0f, 16.0f));

	UFUNCTION(BlueprintPure, Category = "Utilities", meta = (DisplayName = "Get Soft Class Name"))
	static FName GetSoftClassName(const TSoftClassPtr<UObject>& Class);

	UFUNCTION(BlueprintPure, Category = "Utilities", meta = (DisplayName = "Get Soft Class Display Name Text"))
	static FText GetSoftClassDisplayNameText(const TSoftClassPtr<UObject>& Class);

	UFUNCTION(BlueprintPure, Category = "Utilities", meta = (DisplayName = "Get Class Display Name Text"))
	static FText GetClassDisplayNameText(const UClass* Class);

	UFUNCTION(BlueprintPure, Category = "Utilities", meta = (DisplayName = "Get Soft Object Name"))
	static FName GetSoftObjectName(const TSoftObjectPtr<UObject>& Object);


	/* Get Component reference.
	* If Actor reference is not set, FallbackActor will be used.
	*/
	UFUNCTION(BlueprintCallable, Category = "Utilities", meta = (DefaultToSelf = "FallbackActor", DisplayName = "Get Component"))
	static UActorComponent* GetComponentReferenceComponent(UPARAM(ref) const FComponentReference& Target, AActor* FallbackActor);


	/** Searches components array and returns first encountered component with the specified name. */
	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (DefaultToSelf = "Target", ComponentClass = "ActorComponent", ComponentName, DeterminesOutputType = "ComponentClass"))
	static UActorComponent* GetComponentByName(AActor* Target, TSubclassOf<UActorComponent> ComponentClass, FName ComponentName);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (GameplayTag)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameplayTags")
	static FString Conv_GameplayTagToString(const FGameplayTag& GameplayTag);


	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Name (GameplayTag)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameplayTags")
	static FName Conv_GameplayTagToName(const FGameplayTag& GameplayTag);

	UFUNCTION(BlueprintCallable, Category = "Utilities|String")
	static void ToDisplayString(const FString String, FString& DisplayString, const bool bIsBool = false);
	
	UFUNCTION(BlueprintCallable, Category = "Level Editor", meta=(WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", HidePin = "WorldContextObject", DevelopmentOnly))
	static void FocusViewportToSelection(const UObject* WorldContextObject);

	//UFUNCTION(BlueprintCallable, Category = "Level Editor", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject", HidePin = "WorldContextObject", DevelopmentOnly))
	//static void FocusViewportToActor(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Utilities|String", meta = (DeterminesOutputType = "Class"))
	static TArray<UObject*> CastArray(const TArray<UObject*> Array, const TSubclassOf<UObject> Class);
};
