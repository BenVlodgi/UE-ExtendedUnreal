// Copyright 2023 Dream Seed LLC.

#pragma once


#include "Kismet/KismetArrayLibrary.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExtendedArrayLibrary.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintThreadSafe))
class EXTENDEDUNREAL_API UExtendedArrayLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Utilities", meta = (DeterminesOutputType = "Class"))
	static TArray<UObject*> CastArray(const TArray<UObject*> Array, const TSubclassOf<UObject> Class);

	/* 
	 *Remove all instances of items from array.
	 *
	 *@param	TargetArray		The array to remove from
	 *@param	Items			The items to remove from the array
	 *@return	True if one or more items were removed
	*/
	UFUNCTION(BlueprintCallable, CustomThunk, meta=(DisplayName = "Remove Items", CompactNodeTitle = "REMOVE ITEMS", ArrayParm = "TargetArray", ArrayTypeDependentParams = "Items", AutoCreateRefTerm = "Items"), Category="Utilities|Array")
	static bool Array_RemoveItems(const TArray<int32>& TargetArray, const TArray<int32>& Items);

	DECLARE_FUNCTION(execArray_RemoveItems)
	{
		Stack.MostRecentProperty = nullptr;

		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* TargetArrayAddr = Stack.MostRecentPropertyAddress;
		FArrayProperty* TargetArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		if (!TargetArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* ItemsArrayAddr = Stack.MostRecentPropertyAddress;
		FArrayProperty* ItemsArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		if (!ItemsArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}
		P_FINISH;

		P_NATIVE_BEGIN;
		MARK_PROPERTY_DIRTY(Stack.Object, TargetArrayProperty);
		MARK_PROPERTY_DIRTY(Stack.Object, ItemsArrayProperty);
		*(bool*)RESULT_PARAM = GenericArray_RemoveItems(TargetArrayAddr, TargetArrayProperty, ItemsArrayAddr, ItemsArrayProperty);
		P_NATIVE_END;
	}

	static bool GenericArray_RemoveItems(void* TargetArray, const FArrayProperty* TargetArrayProp, void* ItemsArray, const FArrayProperty* ItemsArrayProp);


	/**
	 * Outputs a Set containing copies of the entries of an Array.
	 *
	 * @param		A		Array
	 * @param		Result	Set
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (DisplayName = "To Set", CompactNodeTitle = "TO SET", SetParam = "A|Result"), Category = "Utilities|Array")
	static void Array_ToSet(const TArray<int32>& A, TSet<int32>& Result);

	DECLARE_FUNCTION(execArray_ToSet)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* TargetArrayAddr = Stack.MostRecentPropertyAddress;
		FArrayProperty* TargetArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		if (!TargetArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FSetProperty>(NULL);
		void* SetAddr = Stack.MostRecentPropertyAddress;
		FSetProperty* SetProperty = CastField<FSetProperty>(Stack.MostRecentProperty);
		if (!SetProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_FINISH;

		P_NATIVE_BEGIN;
		GenericArray_ToSet(TargetArrayAddr, TargetArrayProperty, SetAddr, SetProperty);
		P_NATIVE_END;
	}

	static void GenericArray_ToSet(const void* TargetArray, const FArrayProperty* ArrayProperty, void* TargetSet, const FSetProperty* SetProperty);

};
