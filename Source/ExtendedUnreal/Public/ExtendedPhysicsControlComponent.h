// Copyright 

#pragma once

#include "CoreMinimal.h"
#include "PhysicsControlComponent.h"
#include "ExtendedPhysicsControlComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class EXTENDEDUNREAL_API UExtendedPhysicsControlComponent : public UPhysicsControlComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "PhysicsControl")
	void ToggleControlZAxisForce(FName Name);
	
};
