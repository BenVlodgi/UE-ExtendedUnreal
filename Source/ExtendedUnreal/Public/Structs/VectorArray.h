// Copyright 2024 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VectorArray.generated.h"

/** Array of Vectors.
 * Useful to use as the value in a dictionary/hash.
 */
USTRUCT(BlueprintType)
struct EXTENDEDUNREAL_API FVectorArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<FVector> Array;
};
