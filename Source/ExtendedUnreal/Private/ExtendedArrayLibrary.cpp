// Copyright 2023 Dream Seed LLC.


#include "ExtendedArrayLibrary.h"
#include "Kismet/BlueprintSetLibrary.h"



TArray<UObject*> UExtendedArrayLibrary::CastArray(const TArray<UObject*> Array, const TSubclassOf<UObject> Class)
{
	return Array;
}

bool UExtendedArrayLibrary::Array_RemoveItems(const TArray<int32>& TargetArray, const TArray<int32>& Items)
{
	// We should never hit these!  They're stubs to avoid NoExport on the class.  Call the Generic* equivalent instead
	check(0);
	return true;
}

bool UExtendedArrayLibrary::GenericArray_RemoveItems(void* TargetArray, const FArrayProperty* TargetArrayProp, void* ItemsArray, const FArrayProperty* ItemsArrayProp)
{
	bool bRemoved = false;

	if (TargetArray && ItemsArray)
	{
		FScriptArrayHelper TargetArrayHelper(TargetArrayProp, TargetArray);
		FScriptArrayHelper ItemsArrayHelper(ItemsArrayProp, ItemsArray);
		if (TargetArrayHelper.Num() > 0 && ItemsArrayHelper.Num() > 0)
		{
			for (int32 TargetArrayIndex = 0; TargetArrayIndex < TargetArrayHelper.Num(); TargetArrayIndex++)
			for (int32 ItemsArrayIndex = 0; ItemsArrayIndex < ItemsArrayHelper.Num(); ItemsArrayIndex++)
			{
				if (ItemsArrayProp->Inner->Identical(TargetArrayHelper.GetRawPtr(TargetArrayIndex), ItemsArrayHelper.GetRawPtr(ItemsArrayIndex)))
				{
					TargetArrayHelper.RemoveValues(TargetArrayIndex, 1);
					bRemoved = true;
				}
			}
		}
	}

	return bRemoved;
}

void UExtendedArrayLibrary::Array_ToSet(const TArray<int32>& A, TSet<int32>& Result)
{
	// We should never hit these!  They're stubs to avoid NoExport on the class.  Call the Generic* equivalent instead
	check(0);
}

void UExtendedArrayLibrary::GenericArray_ToSet(const void* TargetArray, const FArrayProperty* ArrayProperty, void* TargetSet, const FSetProperty* SetProperty)
{
	if (TargetSet && TargetArray)
	{
		// Clear the Set first
		FScriptSetHelper SetHelper(SetProperty, TargetSet);
		SetHelper.EmptyElements();

		FScriptArrayHelper ArrayHelper(ArrayProperty, TargetArray);
		const int32 Size = ArrayHelper.Num();
		for (int32 I = 0; I < Size; ++I)
		{
			SetHelper.AddElement(ArrayHelper.GetRawPtr(I));
		}
	}
}

