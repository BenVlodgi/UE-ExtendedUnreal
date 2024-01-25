// Copyright 2023 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DelegateHandleWrapper.generated.h"

/**
 * Delegate Handle holds ID of a delegate, used for unbinding.
 */
USTRUCT(BlueprintType)
struct EXTENDEDUNREAL_API FDelegateHandleWrapper
{
	GENERATED_BODY()

public:
	FDelegateHandle DelegateHandle;

	friend FORCEINLINE uint32 GetTypeHash(const FDelegateHandleWrapper& Handle)
	{
		return GetTypeHash(Handle.DelegateHandle);
	}
};
