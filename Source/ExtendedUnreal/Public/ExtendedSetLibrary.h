// Copyright 2023 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExtendedSetLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedSetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Utilities", meta = (DeterminesOutputType = "Class"))
	static TSet<UObject*> CastSet(const TSet<UObject*> Set, const TSubclassOf<UObject> Class);

	/**
	 * Adds all elements from  OtherSet to the TargetSet.
	 *
	 * @param	TargetSet		The set to search for the item.
	 * @param	OtherSet		The items to add to the set.
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (DisplayName = "Add Set", CompactNodeTitle = "ADD SET", SetParam = "TargetSet|OtherSet", AutoCreateRefTerm = "OtherSet"), Category = "Utilities|Set")
	static void Set_AddSet(const TSet<int32>& TargetSet, const TSet<int32>& OtherSet);

	DECLARE_FUNCTION(execSet_AddSet)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FSetProperty>(NULL);
		void* SetAddr = Stack.MostRecentPropertyAddress;
		FSetProperty* SetProperty = CastField<FSetProperty>(Stack.MostRecentProperty);
		if (!SetProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FSetProperty>(NULL);
		void* OtherSetAddr = Stack.MostRecentPropertyAddress;
		FSetProperty* OtherSetProperty = CastField<FSetProperty>(Stack.MostRecentProperty);
		if (!OtherSetProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_FINISH;

		P_NATIVE_BEGIN;
		GenericSet_AddSet(SetAddr, SetProperty, OtherSetAddr, OtherSetProperty);
		P_NATIVE_END;
	}

	static void GenericSet_AddSet(const void* TargetSet, const FSetProperty* SetProperty, const void* OtherSetPtr, const FSetProperty* OtherSetProperty);
	
};
