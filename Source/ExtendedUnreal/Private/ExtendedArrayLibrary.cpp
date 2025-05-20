// Copyright 2023 Dream Seed LLC.


#include "ExtendedArrayLibrary.h"
#include "Kismet/BlueprintSetLibrary.h"
//#include "Containers/Array.h"



TArray<UObject*> UExtendedArrayLibrary::CastArray(const TArray<UObject*> Array, const TSubclassOf<UObject> Class, const bool bRemoveNull)
{
	if (bRemoveNull)
	{
		TArray<UObject*> Succeeded;
		for (const auto& Object : Array)
		{
			if (Object->GetClass()->IsChildOf(Class))
			{
				Succeeded.Add(Object);
			}
		}
		return Succeeded;
	}
	else
	{
		return Array;
	}
}

void UExtendedArrayLibrary::FilterArrayForInterface(const TArray<UObject*>& TargetArray, TSubclassOf<UInterface> Interface, TArray<UObject*>& FilteredArray)
{
	FilteredArray.Empty();

	if (!Interface)
	{
		UE_LOG(LogTemp, Warning, TEXT("FilterArrayForInterface: Interface provided was null."));
		return;
	}
	if (Interface)
	{
		checkf(Interface->IsChildOf(UInterface::StaticClass()), TEXT("Interface parameter %s is not actually an interface."), *Interface->GetName());
	}


	for (const auto& Object : TargetArray)
	{
		if (IsValid(Object) && Object->GetClass()->ImplementsInterface(Interface))
		{
			FilteredArray.Add(Object);
		}
	}
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

void UExtendedArrayLibrary::GenericArray_Resolve(const void* TargetArrayAddress, const FArrayProperty* TargetArrayProperty, void* ReturnArrayAddress, const FArrayProperty* ReturnArrayProperty)
{
	if (!ReturnArrayAddress || !ReturnArrayProperty || !ReturnArrayProperty)
	{
		return;
	}

	if (!TargetArrayAddress || !TargetArrayProperty || !TargetArrayProperty->Inner)
	{
		// Without a valid target array, lets clear the output and be done.
		FScriptArrayHelper ReturnArrayHelper(ReturnArrayProperty, ReturnArrayAddress);
		ReturnArrayHelper.EmptyValues();
		return;
	}

	FProperty* TargetProperty = TargetArrayProperty->Inner;
	FProperty* ReturnProperty = ReturnArrayProperty->Inner;

	FScriptArrayHelper TargetArrayHelper(TargetArrayProperty, TargetArrayAddress);
	FScriptArrayHelper ReturnArrayHelper(ReturnArrayProperty, ReturnArrayAddress);

	const int32 Size = TargetArrayHelper.Num();
	ReturnArrayHelper.EmptyAndAddValues(Size);

	const bool bInputIsSoft = TargetArrayProperty->Inner->IsA<FSoftObjectProperty>(); // This includes FSoftClassProperty
	const bool bOutputIsSoft = ReturnArrayProperty->Inner->IsA<FSoftObjectProperty>(); // This includes FSoftClassProperty

	const bool bInputIsClass = TargetArrayProperty->Inner->IsA<FClassProperty>() || TargetArrayProperty->Inner->IsA<FSoftClassProperty>();
	const bool bInputIsObject = TargetArrayProperty->Inner->IsA<FObjectProperty>() || TargetArrayProperty->Inner->IsA<FSoftObjectProperty>(); // this will also be true when it's a class.

	const bool bOutputIsClass = ReturnArrayProperty->Inner->IsA<FClassProperty>() || ReturnArrayProperty->Inner->IsA<FSoftClassProperty>();
	const bool bOutputIsObject = ReturnArrayProperty->Inner->IsA<FObjectProperty>() || ReturnArrayProperty->Inner->IsA<FSoftObjectProperty>(); // this will also be true when it's a class.



	for (int32 Index = 0; Index < Size; ++Index)
	{
		TSoftClassPtr<UObject> SoftClass;
		UClass* HardClass = nullptr;
		TSoftObjectPtr<UObject> SoftObject;
		UObject* HardObject = nullptr;

		// Copy out of target
		if (bInputIsClass)
		{
			if (bInputIsSoft)
			{
				TargetProperty->CopyCompleteValueFromScriptVM(&SoftClass, TargetArrayHelper.GetRawPtr(Index));
				HardClass = SoftClass.Get();
				HardObject = HardClass;
				SoftObject = HardObject;
			}
			else
			{
				TargetProperty->CopyCompleteValueFromScriptVM(&HardClass, TargetArrayHelper.GetRawPtr(Index));
				SoftClass = HardClass;
				HardObject = HardClass;
				SoftObject = HardObject;
			}
		}
		else if (bInputIsObject)
		{
			if (bInputIsSoft)
			{
				TargetProperty->CopyCompleteValueFromScriptVM(&SoftObject, TargetArrayHelper.GetRawPtr(Index));
				HardObject = SoftObject.Get();
				HardClass = HardObject->GetClass();
				SoftClass = HardClass;
			}
			else
			{
				TargetProperty->CopyCompleteValueFromScriptVM(&HardObject, TargetArrayHelper.GetRawPtr(Index));
				SoftObject = HardObject;
				HardClass = HardObject->GetClass();
				SoftClass = HardClass;
			}
		}

		// Copy to output
		if (bOutputIsClass)
		{
			if (bOutputIsSoft)
			{
				ReturnProperty->CopyCompleteValueToScriptVM(ReturnArrayHelper.GetRawPtr(Index), &SoftClass);
			}
			else
			{
				ReturnProperty->CopyCompleteValueToScriptVM(ReturnArrayHelper.GetRawPtr(Index), &HardClass);
			}
		}
		else if (bOutputIsObject)
		{
			if (bOutputIsSoft)
			{
				ReturnProperty->CopyCompleteValueToScriptVM(ReturnArrayHelper.GetRawPtr(Index), &SoftObject);
			}
			else
			{
				ReturnProperty->CopyCompleteValueToScriptVM(ReturnArrayHelper.GetRawPtr(Index), &HardObject);
			}
		}
	}
}

//void UExtendedArrayLibrary::GenericArray_Diff(const void* TargetArray, const FArrayProperty* ArrayProperty, const void* OtherArray, const FArrayProperty* OtherArrayProperty, void* AddedArray, FArrayProperty* AddedArrayProperty, void* RemovedArray, FArrayProperty* RemovedArrayProperty)
//{
//	//FScriptSetHelper SetHelper(SetProperty, TargetSet);
//	//TSet<double> DoubleSet;
//	//DoubleSet.Difference();
//
//	//FScriptArrayHelper ArrayHelper(ArrayProperty, TargetArray);
//	
//	//TArray<int> IntArray;
//
//	//IntArray.FilterByPredicate();
//}


namespace StringSorting
{
	FString StripLeadingZeros(const FString& Num)
	{
		int32 NonZeroIndex = 0;
		while (NonZeroIndex < Num.Len() && Num[NonZeroIndex] == '0') NonZeroIndex++;
		return NonZeroIndex == Num.Len() ? TEXT("0") : Num.Mid(NonZeroIndex);
	}

	int CompareSegments(const FString& A, const FString& B)
	{
		FString CleanA = StripLeadingZeros(A);
		FString CleanB = StripLeadingZeros(B);

		if (CleanA.Len() != CleanB.Len()) return CleanA.Len() < CleanB.Len() ? -1 : 1;

		return CleanA.Compare(CleanB);
	}

	int32 NaturalCompare(const FString& A, const FString& B, bool bGroupNumbers)
	{
		if (!bGroupNumbers) return A.Compare(B);

		int32 IndexA = 0, IndexB = 0;

		while (IndexA < A.Len() && IndexB < B.Len())
		{
			if (FChar::IsDigit(A[IndexA]) && FChar::IsDigit(B[IndexB]))
			{
				int32 StartA = IndexA, StartB = IndexB;
				while (IndexA < A.Len() && FChar::IsDigit(A[IndexA])) IndexA++;
				while (IndexB < B.Len() && FChar::IsDigit(B[IndexB])) IndexB++;

				int Result = CompareSegments(A.Mid(StartA, IndexA - StartA), B.Mid(StartB, IndexB - StartB));
				if (Result != 0) return Result;
			}
			else
			{
				TCHAR CharA = A[IndexA++];
				TCHAR CharB = B[IndexB++];
				if (CharA != CharB) return CharA < CharB ? -1 : 1;
			}
		}

		return A.Len() - B.Len();
	}
}

void UExtendedArrayLibrary::SortStringArrayInPlace(TArray<FString>& Strings, const bool Reversed, const bool bGroupNumbers)
{
	Strings.Sort([=](const FString& A, const FString& B)
		{
			int32 Result = StringSorting::NaturalCompare(A, B, bGroupNumbers);
			return Reversed ? Result > 0 : Result < 0;
		});
}

void UExtendedArrayLibrary::SortNameArrayInPlace(TArray<FName>& Names, const bool Reversed, const bool bGroupNumbers)
{
	Names.Sort([=](const FName& A, const FName& B)
		{
			int32 Result = StringSorting::NaturalCompare(A.ToString(), B.ToString(), bGroupNumbers);
			return Reversed ? Result > 0 : Result < 0;
		});
}
