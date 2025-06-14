// Copyright 2025 Dream Seed LLC.

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


	/**
	 * Generates a list of points around a circle on the XY plane.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Points in Circle", Keywords = "ring"), Category = "Math")
	static TArray<FVector> GetPointsInCircle(const FTransform& Transform, const double Radius, const int32 NumPoints);

	static FVector ClosestPointOnBox(const FVector& Point, const FTransform& BoxTransform, const FVector& BoxExtents);
	static FVector ClosestPointOnCapsule(const FVector& Point, const FVector& CapsuleLocation, const FRotator& CapsuleRotation, float CapsuleRadius, float CapsuleHalfHeight);

	/**
	 * Returns the closest point in a box to a given world-space point.
	 *
	 * @param BoxTransform		The transform of the box in world space.
	 * @param BoxExtents		The extents of the box in local space.
	 * @param Point				The point in world space to find the closest point to.
	 * @param bClampToSurface	When true, the point will be clamped to the box's surface if it is inside.
	 * @param bIsInside			True if the point iss inside the box, false if it is outside.
	 * @param ClosestPoint		The closest point on the box to the given point.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Geometry", meta = (KeyWords = "ClosestPointOnBox"))
	void ClosestPointInBox(const FTransform& BoxTransform, const FVector& BoxExtents, const FVector& Point, bool bClampToSurface, bool& bIsInside, FVector& ClosestPoint);

	/**
	 * Returns the closest point in a vertical capsule to a given world-space point.
	 *
	 * @param CapsuleLocation	The location of the capsule in world space.
	 * @param CapsuleRotation	The rotation of the capsule in world space.
	 * @param CapsuleRadius	The radius of the capsule.
	 * @param CapsuleHalfHeight	The half height of the capsule.
	 * @param Point				The point in world space to find the closest point to.
	 * @param bClampToSurface	When true, the point will be clamped to the capsule's surface if it is inside.
	 * @param bIsInside			True if the point is inside the capsule, false if it is outside.
	 * @param ClosestPoint		The closest point on the capsule to the given point.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Geometry")
	void ClosestPointInCapsule(const FVector& CapsuleLocation, const FRotator& CapsuleRotation, float CapsuleRadius, float CapsuleHalfHeight, const FVector& Point, const bool bClampToSurface, bool& bIsInside, FVector& ClosestPoint);


	/** Returns true if the outer sphere fully encloses the inner sphere (using centers and radii). */
	UFUNCTION(BlueprintPure, Category = "Math|Geometry")
	static bool SphereEnclosesSphere(const FVector& OuterCenter, double OuterRadius, const FVector& InnerCenter, double InnerRadius);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Angle Distance (Degrees)"), Category = "Math")
	static UPARAM(DisplayName = "Distance") double AngleDistanceDegrees(double A, double B);

	// UNTESTED
	UFUNCTION(BlueprintCallable, Category = "Rotator")
	static void GetAxisAndAngleBetweenRotators(const FRotator& A, const FRotator& B, FVector& Axis, double& Angle);

	// UNTESTED
	UFUNCTION(BlueprintCallable, Category = "Vector")
	static void GetAxisAndAngleBetweenVectors(const FVector& A, const FVector& B, FVector& Axis, double& Angle);

	// DOESN'T WORK
	// If the Axis is invalid, the result will be 0.
	UFUNCTION(BlueprintPure, Category = "Rotator")
	static UPARAM(DisplayName = "Angle") double GetRotatorAngleRelativeToAxis(const FRotator Rotator, const FVector Axis);

	// Return the number closer to the Reference.
	UFUNCTION(BlueprintPure, Category = "Float")
	static UPARAM(DisplayName = "Nearest") double Nearest(const double Reference, const double A, const double B);

	UFUNCTION(BlueprintPure, Category = "Float")
	static UPARAM(DisplayName = "Nearest Angle") double NearestAngle(const double ReferenceAngle, const double AngleA, const double AngleB, UPARAM(DisplayName = "A is Nearest") bool& bAIsNearest);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Lerp Angle (Degrees)"), Category = "Float")
	static UPARAM(DisplayName = "Angle") double LerpAngleDegrees(double A, double B, double Alpha);

	UFUNCTION(BlueprintCallable, Category = "Math")
	static UPARAM(DisplayName = "Normal")FVector CalculateTriangleNormal(const FVector& Vertex1, const FVector& Vertex2, const FVector& Vertex3);

	UFUNCTION(BlueprintCallable, Category = "Math")
	static UPARAM(DisplayName = "Up Normal") FVector CalculateEdgeUpDirection(const FVector& Vertex1, const FVector& Vertex2);

	/**
	 * Returns a random index based on the provided WeightedArray.
	 *
	 * @param WeightedArray	Array of non-negative weights. Higher weight = higher chance of being selected. Zero and negative weights are ignored.
	 * @return				The selected index based on the weight distribution, or INDEX_NONE if weights are invalid.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Random", meta = (NotBlueprintThreadSafe))
	static int32 RandomWeightedArrayItem(const TArray<double>& WeightedArray);

	/**
	 * Returns a random index based on the provided WeightedArray using a deterministic random stream.
	 *
	 * @param Stream		Random stream to use for deterministic randomness.
	 * @param WeightedArray	Array of non-negative weights. Higher weight = higher chance of being selected. Zero and negative weights are ignored.
	 * @return				The selected index based on the weight distribution, or INDEX_NONE if weights are invalid.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Random")
	static int32 RandomWeightedArrayItemFromStream(const FRandomStream& Stream, const TArray<double>& WeightedArray);

};
