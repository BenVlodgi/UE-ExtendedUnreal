// Copyright 2023 Dream Seed LLC.

#pragma once

#include "Engine/EngineTypes.h"
#include "Units/RigUnit.h"


#include "RigUnit_SphereTraceProfile.generated.h"


/**
 * Sweeps a sphere against the world and return the first blocking hit using a specific profile.
 * You can create custom trace profiles in Project Setting - Collision.
 */
USTRUCT(meta = (DisplayName = "Sphere Trace By Profile", Category = "Collision", DocumentationPolicy = "Strict", Keywords = "Sweep,Raytrace,Collision,Collide,Trace", Varying, NodeColor = "0.2 0.4 0.7"))
struct EXTENDEDUNREAL_API FRigUnit_SphereTraceByProfile : public FRigUnit
{
	GENERATED_BODY()

	FRigUnit_SphereTraceByProfile()
		: Start(EForceInit::ForceInitToZero)
		, End(EForceInit::ForceInitToZero)
		, ProfileName(FName())
		, Radius(5.f)
		, bHit(false)
		, HitLocation(EForceInit::ForceInitToZero)
		, HitNormal(0.f, 0.f, 1.f)
	{
	}

	RIGVM_METHOD()
	virtual void Execute() override;

	/** Start of the trace in rig / global space */
	UPROPERTY(meta = (Input))
	FVector Start;

	/** End of the trace in rig / global space */
	UPROPERTY(meta = (Input))
	FVector End;

	/** The 'profile' that this trace sweeps with, used to determine which components to hit */
	UPROPERTY(meta = (Input, DisplayName = "Profile", GetOptions = "Engine.KismetSystemLibrary.GetCollisionProfileNames"))
	FName ProfileName;

	/** Radius of the sphere to use for sweeping / tracing */
	UPROPERTY(meta = (Input, UIMin = "0.0", UIMax = "100.0"))
	float Radius;

	//// Rig Unit doesn't support Object references
	///** Actors to be ignored by this sweep / trace. Owning actor is already ignored. */
	//UPROPERTY(meta = (Input))
	//TArray<TObjectPtr<AActor>> ActorsToIgnore;

	/** Returns true if there was a hit */
	UPROPERTY(meta = (Output))
	bool bHit;

	/** Hit location in rig / global Space */
	UPROPERTY(meta = (Output))
	FVector HitLocation;

	/** Hit normal in rig / global Space */
	UPROPERTY(meta = (Output))
	FVector HitNormal;
};