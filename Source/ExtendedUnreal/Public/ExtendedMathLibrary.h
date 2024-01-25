// Copyright 2023 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExtendedMathLibrary.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintThreadSafe))
class EXTENDEDUNREAL_API UExtendedMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 * Calculate the signed distance (in the direction of the normal) between a point and a plane.
	 *
	 * @param Location The Location we are checking against the Plane.
	 * @param Plane The Plane the Location will be checked against.
	 * @return Signed distance between location and plane.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Plane", meta = (Keywords = "point, location"))
	static double SignedDistanceFromPlane(const FPlane& Plane, const FVector& Location);


	/** Returns true if A is nearly equal to B (A ~== B) within a small tollerance. */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (Plane)", CompactNodeTitle = "==", Keywords = "== equal"), Category = "Math|Plane")
	static bool EqualEqual_Plane(const FPlane& A, const FPlane& B);


	/**
	 * Get a flipped version of the plane.
	 *
	 * @return A flipped version of the plane.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Plane", meta = (Keywords = ""))
	static FPlane Flip(const FPlane& Plane);


	/**
	 * Checks if this plane is valid (ie: if it has a non-zero normal).
	 *
	 * @return true if the plane is well-defined (has a non-zero normal), otherwise false.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Plane", meta = (Keywords = ""))
	static bool IsValid(const FPlane& Plane);

	/**
	 * Get the origin of this plane.
	 *
	 * @return The origin (base point) of this plane.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Plane", meta = (Keywords = "location"))
	static FVector GetOrigin(const FPlane& Plane);


	/**
	 * Get the normal of this plane.
	 *
	 * @return The normal of this plane.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Plane", meta = (Keywords = ""))
	static const FVector GetNormal(const FPlane& Plane);


	/**
	 * Calculates distance between plane and a location.
	 *
	 * @param Location The other location.
	 * @return The distance from the plane to the location.\n 0: Location is on the plane.\n >0: Location is in front of the plane.\n <0: Location is behind the plane.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Plane", meta = (DisplayName = "Plane Dot (Distance)", Keywords = "distance"))
	static double PlaneDot(const FPlane& Plane, const FVector& Location);

	/**
	 * Calculates dot product of two planes (A | B).
	 *
	 * @param A The plane.
	 * @param B The other plane.
	 * @return The dot product.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Plane", meta = (DisplayName = "Dot Product", CompactNodeTitle = "dot", ScriptMethod = "Dot", ScriptOperator = "|"))
	static double Dot(const FPlane& A, const FPlane& B);


	/**
	 * Computes a relative rotator of one rotator compared to another.
	 *
	 * Example: ChildOffset = MakeRelativeRotator(Child.GetActorRotation(), Parent.GetActorRotation())
	 * This computes the relative rotator of the Child from the Parent.
	 *
	 * @param		A				The object's rotator
	 * @param		RelativeTo		The rotator the result is relative to (in the same space as A)
	 * @return		The new relative rotator
	 */
	UFUNCTION(BlueprintPure, meta = (ScriptMethod = "MakeRelative", Keywords = "convert, torelative"), Category = "Math|Rotator")
	static FRotator MakeRelativeRotator(const FRotator& A, const FRotator& RelativeTo);

	UFUNCTION(BlueprintCallable, meta = (Keywords = ""), Category = "Math|Vector")
	static double VectorLengthAlongDirection(const FVector& Vector, const FVector& Direction);

	/**
	 * Set this vector's length in-place. If the vector is 0 length, it will remain that way.
	 *
	 * @param Tolerance Minimum squared length of vector for normalization.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Length In Place (Vector)", Keywords = "size"), Category = "Math|Vector")
	static void Vector_SetLength(UPARAM(ref) FVector& Vector, const double Length);

};
