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

	/** Returns true if this was ever bound to a delegate, but you need to check with the owning delegate to confirm it is still valid */
	bool IsValid() const
	{
		return DelegateHandle.IsValid();
	}

	/** Clear handle to indicate it is no longer bound */
	void Reset()
	{
		DelegateHandle.Reset();
	}

	bool operator==(const FDelegateHandleWrapper& Other) const
	{
		return DelegateHandle == Other.DelegateHandle;
	}

	bool operator!=(const FDelegateHandleWrapper& Other) const
	{
		return DelegateHandle != Other.DelegateHandle;
	}
	
public:

	friend FORCEINLINE uint32 GetTypeHash(const FDelegateHandleWrapper& Handle)
	{
		return GetTypeHash(Handle.DelegateHandle);
	}

};
