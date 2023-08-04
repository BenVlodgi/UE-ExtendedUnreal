// Copyright 2023 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExtendedMapLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedMapLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/** 
	 * Finds keys who's value match the target Value.
	 *
	 * @param	TargetMap		The map to perform the lookup on
	 * @param	Value			The value that will be used to look the keys up
	 * @param	Keys			The keys associated with the value, default constructed if value was not found
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, meta=(DisplayName = "Find Keys by Value", CompactNodeTitle = "FIND KEYS BY VALUE", MapParam = "TargetMap", MapKeyParam = "Keys", MapValueParam = "Value", AutoCreateRefTerm = "Value", BlueprintThreadSafe), Category = "Utilities|Map")
	static void Map_FindKeysByValue(const TMap<int32, int32>& TargetMap, const int32& Value, TArray<int32>& Keys);

	DECLARE_FUNCTION(execMap_FindKeysByValue)
	{
		// Map //
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FMapProperty>(NULL);
		void* MapAddr = Stack.MostRecentPropertyAddress;
		FMapProperty* MapProperty = CastField<FMapProperty>(Stack.MostRecentProperty);
		if (!MapProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		// Value //
		const FProperty* SearchValueProperty = MapProperty->ValueProp;
		const int32 ValuePropertySize = SearchValueProperty->ElementSize * SearchValueProperty->ArrayDim;
		void* SearchValueStorageSpace = FMemory_Alloca(ValuePropertySize);
		SearchValueProperty->InitializeValue(SearchValueStorageSpace);

		Stack.MostRecentPropertyAddress = nullptr;
		Stack.MostRecentPropertyContainer = nullptr;
		Stack.StepCompiledIn<FProperty>(SearchValueStorageSpace);

		// Keys //
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* KeysAddr = Stack.MostRecentPropertyAddress;
		FArrayProperty* KeysProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		if (!KeysProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}
		////

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericMap_FindKeysByValue(MapAddr, MapProperty, SearchValueStorageSpace, KeysAddr, KeysProperty);
		P_NATIVE_END;

		SearchValueProperty->DestroyValue(SearchValueStorageSpace);
	}

	static void GenericMap_FindKeysByValue(const void* TargetMap, const FMapProperty* MapProperty, const void* ValuePtr, void* KeysPtr, FArrayProperty* KeysProperty);
	
};
