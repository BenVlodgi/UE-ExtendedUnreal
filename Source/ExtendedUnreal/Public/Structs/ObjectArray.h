// Copyright 2022 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectArray.generated.h"

/** Array of Objects.
 * Useful to use as the value in a dictionary/hash.
 */
USTRUCT(BlueprintType)
struct EXTENDEDUNREAL_API FObjectArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<TObjectPtr<UObject>> Array;
};
