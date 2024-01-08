// Copyright 2023 Dream Seed LLC.


#include "ExtendedSetLibrary.h"

#include "Kismet/BlueprintSetLibrary.h"


TSet<UObject*> UExtendedSetLibrary::CastSet(const TSet<UObject*> Set, const TSubclassOf<UObject> Class)
{
	return Set;
}

void UExtendedSetLibrary::GenericSet_AddSet(const void* TargetSetPtr, const FSetProperty* SetProperty, const void* OtherSetPtr, const FSetProperty* OtherSetProperty)
{
	if (TargetSetPtr && OtherSetPtr)
	{
		FScriptSetHelper SetHelper(OtherSetProperty, OtherSetPtr);

		const int32 Size = SetHelper.Num();
		for (int32 I = 0; I < Size; ++I)
		{
			UBlueprintSetLibrary::GenericSet_Add(TargetSetPtr, SetProperty, SetHelper.GetElementPtr(I));
		}
	}
}
