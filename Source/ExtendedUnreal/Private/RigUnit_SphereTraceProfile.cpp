// Copyright 2023 Dream Seed LLC.


#include "RigUnit_SphereTraceProfile.h"


#include "Engine/World.h"
#include "Math/ControlRigMathLibrary.h"
#include "Units/RigUnitContext.h"
#include "Components/PrimitiveComponent.h"


FRigUnit_SphereTraceByProfile_Execute()
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_RIGUNIT()

	bHit = false;
	HitLocation = FVector::ZeroVector;
	HitNormal = FVector(0.f, 0.f, 1.f);

	if (ExecuteContext.GetWorld() == nullptr)
	{
		return;
	}

	const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(Radius);
	
	//// Silly Conversion.
	//TArray<const AActor*> Local_ActorsToIgnore;
	//for (const AActor* Actor : ActorsToIgnore) { Local_ActorsToIgnore.Add(Actor);  }

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	//QueryParams.AddIgnoredActors(Local_ActorsToIgnore);

	if (ExecuteContext.GetOwningActor())
	{
		QueryParams.AddIgnoredActor(ExecuteContext.GetOwningActor());
	}
	else if (const UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ExecuteContext.GetOwningComponent()))
	{
		QueryParams.AddIgnoredComponent(PrimitiveComponent);
	}

	FHitResult HitResult;
	bHit = ExecuteContext.GetWorld()->SweepSingleByProfile(HitResult, ExecuteContext.ToWorldSpace(Start), ExecuteContext.ToWorldSpace(End), FQuat::Identity, ProfileName, CollisionShape, QueryParams);

	if (bHit)
	{
		HitLocation = ExecuteContext.ToVMSpace(HitResult.ImpactPoint);
		HitNormal = ExecuteContext.GetToWorldSpaceTransform().InverseTransformVector(HitResult.ImpactNormal);
	}
}
