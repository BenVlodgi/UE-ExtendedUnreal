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

	/*
	 * Cast an array of objects to a given object type..
	 *
	 *@param	TargetArray		The array to filter from
	 *@param	Interface		The interface that acts as the filter, only objects implementing it will be returned.
	 *@return	An array containing only those objects which implement the interface.
	*/
	UFUNCTION(BlueprintCallable, Category = "Utilities|Array", meta = (DeterminesOutputType = "Class", keywords = "cast to", bRemoveNull = "false"))
	static TArray<UObject*> CastArray(const TArray<UObject*> Array, const TSubclassOf<UObject> Class, const bool bRemoveNull);

	/*
	 *Filter an array based on an Interface.
	 *
	 *@param	TargetArray		The array to filter from
	 *@param	Interface		The interface that acts as the filter, only objects implementing it will be returned.
	 *@return	An array containing only those objects which implement the interface.
	*/
	UFUNCTION(BlueprintCallable, Category = "Utilities|Array", meta = (DisplayName = "Filter Array (Interface)", DeterminesOutputType = "TargetArray"))
	static void FilterArrayForInterface(const TArray<UObject*>& TargetArray, TSubclassOf<UInterface> Interface, TArray<UObject*>& FilteredArray);


	////UFUNCTION(BlueprintCallable, Category = "Utilities", DisplayName = "Resolve Array to Soft", meta = (DeterminesOutputType = "Array"))
	////static TArray<TSoftObjectPtr<UObject>> ResolveObjectArrayToSoft(const TArray<UObject*> Array);
	////
	////UFUNCTION(BlueprintCallable, Category = "Utilities", DisplayName = "Resolve Array from Soft", meta = (DeterminesOutputType = "Array"))
	////static TArray<UObject*> ResolveObjectArrayFromSoft(const TArray<TSoftObjectPtr<UObject>> Array);

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



	/**
	 * Outputs a soft/hard array containing copies of the entries of an Array.
	 *
	 * @param		A		Array
	 * @param		Result	Resolved array
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (DisplayName = "Resolve Array", CompactNodeTitle = "RESOLVE", ArrayParm = "A,Result"), Category = "Utilities|Array")
	static void Array_Resolve(const TArray<int32>& A, TArray<int32>& Result);

	DECLARE_FUNCTION(execArray_Resolve)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* TargetArrayAddress = Stack.MostRecentPropertyAddress;
		FArrayProperty* TargetArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		if (!TargetArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* ReturnArrayAddress = Stack.MostRecentPropertyAddress;
		FArrayProperty* ReturnArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		if (!ReturnArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}


		// class is child of object.
		const bool bInputIsClass = TargetArrayProperty->Inner->IsA<FClassProperty>() || TargetArrayProperty->Inner->IsA<FSoftClassProperty>();
		const bool bInputIsObject = TargetArrayProperty->Inner->IsA<FObjectProperty>() || TargetArrayProperty->Inner->IsA<FSoftObjectProperty>(); // this will also be true when it's a class.
		
		const bool bOutputIsClass = ReturnArrayProperty->Inner->IsA<FClassProperty>() || ReturnArrayProperty->Inner->IsA<FSoftClassProperty>();
		const bool bOutputIsObject = ReturnArrayProperty->Inner->IsA<FObjectProperty>() || ReturnArrayProperty->Inner->IsA<FSoftObjectProperty>(); // this will also be true when it's a class.

		if (!bInputIsObject || !bOutputIsObject)
		{
			// They should both be "objects".
			Stack.KismetExecutionMessage(TEXT("Input and output should both be type 'Object' or 'Class'."), ELogVerbosity::Warning);
			Stack.bArrayContextFailed = true;
			return;
		}

		if (bInputIsClass != bOutputIsClass)
		{
			// If input is class that should match output.
			Stack.KismetExecutionMessage(TEXT("Input and output don't match. One is type 'Class', the other is type 'Object'."), ELogVerbosity::Warning);
			Stack.bArrayContextFailed = true;
			return;
		}


		const bool bInputIsSoft = TargetArrayProperty->Inner->IsA<FSoftObjectProperty>(); // This includes FSoftClassProperty
		const bool bOutputIsSoft = ReturnArrayProperty->Inner->IsA<FSoftObjectProperty>(); // This includes FSoftClassProperty

		if (bInputIsSoft == bOutputIsSoft)
		{
			// They should be different.
			Stack.KismetExecutionMessage(TEXT("To to resolve to or from Soft not to the same type."), ELogVerbosity::Warning);
			Stack.bArrayContextFailed = true;
			return;
		}



		P_FINISH;

		P_NATIVE_BEGIN;
		
		GenericArray_Resolve(TargetArrayAddress, TargetArrayProperty, ReturnArrayAddress, ReturnArrayProperty);
		
		P_NATIVE_END;
	}

	static void GenericArray_Resolve(const void* TargetArray, const FArrayProperty* ArrayProperty, void* ReturnArray, const FArrayProperty* ReturnArrayProperty);






	static void GenericArray_Diff(const void* TargetArray, const FArrayProperty* ArrayProperty, const void* OtherArray, const FArrayProperty* OtherArrayProperty, void* AddedArray, FArrayProperty* AddedArrayProperty, void* RemovedArray, FArrayProperty* RemovedArrayProperty);

};
