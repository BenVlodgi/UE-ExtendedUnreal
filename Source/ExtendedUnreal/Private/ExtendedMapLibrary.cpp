// Copyright 2023 Dream Seed LLC.


#include "ExtendedMapLibrary.h"

void UExtendedMapLibrary::GenericMap_FindKeysByValue(const void* TargetMap, const FMapProperty* MapProperty, const void* ValuePtr, void* KeysArrayPtr, FArrayProperty* KeysArrayProperty)
{
	if (TargetMap && KeysArrayProperty && ensure(MapProperty->KeyProp->GetID() == KeysArrayProperty->Inner->GetID()))
	{
		FScriptMapHelper MapHelper(MapProperty, TargetMap);
		FScriptArrayHelper ArrayHelper(KeysArrayProperty, KeysArrayPtr);
		ArrayHelper.EmptyValues();

		int32 Size = MapHelper.Num();
		for (int32 I = 0; Size; ++I)
		{
			if (MapHelper.IsValidIndex(I) && MapProperty->ValueProp->Identical(ValuePtr, MapHelper.GetValuePtr(I)))
			{
				// Append Key to Array.
				int32 LastIndex = ArrayHelper.AddValue();
				KeysArrayProperty->Inner->CopySingleValueToScriptVM(ArrayHelper.GetRawPtr(LastIndex), MapHelper.GetKeyPtr(I));
			}
			--Size;
		}
	}
}
