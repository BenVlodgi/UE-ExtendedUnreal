// Copyright 2025 Dream Seed LLC.


#include "ExtendedMathLibrary.h"


#include "ExtendedUnrealLibrary.h"
#include "Math/Vector.h"
#include "Math/Plane.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "PhysicsEngine/BodySetup.h"
#include "PhysicsEngine/ConvexElem.h"

double UExtendedMathLibrary::SignedDistanceFromPlane(const FPlane& Plane, const FVector& Location)
{
	return FVector::PointPlaneDist(Location, Plane.GetOrigin(), Plane.GetNormal());
}

bool UExtendedMathLibrary::EqualEqual_Plane(const FPlane& A, const FPlane& B)
{
	return A.Equals(B);
}

FPlane UExtendedMathLibrary::Flip(const FPlane& Plane)
{
	return Plane.Flip();
}

bool UExtendedMathLibrary::IsValid(const FPlane& Plane)
{
	return Plane.IsValid();
}

FVector UExtendedMathLibrary::GetOrigin(const FPlane& Plane)
{
	return Plane.GetOrigin();
}

const FVector UExtendedMathLibrary::GetNormal(const FPlane& Plane)
{
	return Plane.GetNormal();
}

double UExtendedMathLibrary::PlaneDot(const FPlane& Plane, const FVector& Point)
{
	return Plane.PlaneDot(Point);
}

double UExtendedMathLibrary::Dot(const FPlane& A, const FPlane& B)
{
	return A | B;
}

FRotator UExtendedMathLibrary::MakeRelativeRotator(const FRotator& A, const FRotator& RelativeTo)
{
	FQuat AQuat = FQuat(A);
	FQuat InverseQuat = FQuat(RelativeTo.GetInverse());

	return FRotator(InverseQuat * AQuat);
}

double UExtendedMathLibrary::VectorLengthAlongDirection(const FVector& Vector, const FVector& Direction)
{
    // Calculate the vector projection
    double DotProduct = FVector::DotProduct(Vector, Direction);
    double DirectionMagnitudeSquared = Direction.SizeSquared();

    // Ensure that the direction vector is not zero to avoid division by zero
    if (DirectionMagnitudeSquared > 0)
    {
        FVector Projection = (DotProduct / DirectionMagnitudeSquared) * Direction;
        double LengthAlongDirection = Projection.Size();

        return LengthAlongDirection;
    }
    else
    {
        return 0.0;
    }
}

void UExtendedMathLibrary::Vector_SetLength(UPARAM(ref) FVector& Vector, const double Length)
{
    Vector.Normalize();
    Vector *= Length;
}

TArray<FVector> UExtendedMathLibrary::GetPointsInCircle(const FTransform& Transform, const double Radius, const int32 NumPoints)
{
	TArray<FVector> Points;

	if (NumPoints > 0)
	{
		double AngleBetweenPoints = 360.0 / NumPoints;

		for (int32 i = 0; i < NumPoints; i++)
		{
			double Angle = i * AngleBetweenPoints;
			double X = Radius * FMath::Cos(FMath::DegreesToRadians(Angle));
			double Y = Radius * FMath::Sin(FMath::DegreesToRadians(Angle));
			FVector Point = FVector(X, Y, 0);

			Points.Add(Transform.TransformPosition(Point));
		}
	}
	
	return Points;
}

FVector UExtendedMathLibrary::ClosestPointOnBox(const FVector& Point, const FTransform& BoxTransform, const FVector& BoxExtents)
{
	// Transform the point into the box's local space
	FVector LocalPoint = BoxTransform.InverseTransformPosition(Point);

	// Clamp the local point within the box's bounds
	FVector ClampedPoint = LocalPoint.BoundToBox(-BoxExtents * 0.5f, BoxExtents * 0.5f);

	// Transform the clamped point back to world space
	return BoxTransform.TransformPosition(ClampedPoint);
}

FVector UExtendedMathLibrary::ClosestPointOnCapsule(const FVector& Point, const FVector& CapsuleLocation, const FRotator& CapsuleRotation, float CapsuleRadius, float CapsuleHalfHeight)
{
	// TODO: REVIEW THIS FUNCTION. It is using the forward vector for the capsule axis. It is being called externally. Need to ensure it is being used correctly.

	// Compute the capsule's axis direction (forward vector from the rotation)
	FVector CapsuleAxis = CapsuleRotation.Vector();

	// Calculate the capsule's base and tip positions based on location, rotation, and half height
	FVector CapsuleBase = CapsuleLocation - CapsuleAxis * CapsuleHalfHeight;
	FVector CapsuleTip = CapsuleLocation + CapsuleAxis * CapsuleHalfHeight;

	// Find the closest point on the line segment between CapsuleBase and CapsuleTip
	FVector SegmentClosestPoint = FMath::ClosestPointOnSegment(Point, CapsuleBase, CapsuleTip);

	// Compute the vector from the line segment to the query point
	FVector ToPoint = Point - SegmentClosestPoint;

	// If the point is outside the capsule's radius, clamp it to the surface
	if (!ToPoint.IsNearlyZero())
	{
		ToPoint = ToPoint.GetSafeNormal() * CapsuleRadius;
	}

	// Return the closest point on the capsule's surface
	return SegmentClosestPoint + ToPoint;
}

void UExtendedMathLibrary::ClosestPointInBox(const FTransform& BoxTransform, const FVector& BoxExtents, const FVector& Point, bool bClampToSurface, bool& bIsInside, FVector& ClosestPoint)
{
	// Transform the point into the box's local space
	FVector LocalPoint = BoxTransform.InverseTransformPosition(Point);

	// Check if point is inside the box
	bIsInside =
		FMath::Abs(LocalPoint.X) <= BoxExtents.X &&
		FMath::Abs(LocalPoint.Y) <= BoxExtents.Y &&
		FMath::Abs(LocalPoint.Z) <= BoxExtents.Z;

	if (bIsInside && !bClampToSurface)
	{
		// It's inside and we don't want to clamp
		ClosestPoint = Point;
	}
	else
	{
		// Clamp the local point within the box's bounds
		const FVector ClampedPoint = LocalPoint.BoundToBox(-BoxExtents, BoxExtents);

		// Transform the clamped point back to world space
		ClosestPoint = BoxTransform.TransformPosition(ClampedPoint);
	}
}

void UExtendedMathLibrary::ClosestPointInCapsule(const FVector& CapsuleLocation, const FRotator& CapsuleRotation, float CapsuleRadius, float CapsuleHalfHeight, const FVector& Point, const bool bClampToSurface, bool& bIsInside, FVector& ClosestPoint)
{
	const FVector CapsuleAxis = FRotationMatrix(CapsuleRotation).GetScaledAxis(EAxis::Z);
	const FVector CapsuleBase = CapsuleLocation - CapsuleAxis * CapsuleHalfHeight;
	const FVector CapsuleTip = CapsuleLocation + CapsuleAxis * CapsuleHalfHeight;

	// Closest point on the capsule's central line segment
	const FVector SegmentClosestPoint = FMath::ClosestPointOnSegment(Point, CapsuleBase, CapsuleTip);
	const FVector Delta = Point - SegmentClosestPoint;
	const float DistSqr = Delta.SizeSquared();

	// Determine whether the point is inside the capsule
	bIsInside = DistSqr <= FMath::Square(CapsuleRadius);

	if (bIsInside || !bClampToSurface)
	{
		// Point is inside, or we don't want to clamp it
		ClosestPoint = Point;
	}
	else
	{
		// Project to capsule surface
		ClosestPoint = SegmentClosestPoint + Delta.GetSafeNormal() * CapsuleRadius;
	}
}


bool UExtendedMathLibrary::SphereEnclosesSphere(const FVector& OuterCenter, double OuterRadius, const FVector& InnerCenter, double InnerRadius)
{
	const double RadiusMargin = FMath::Abs(OuterRadius) - FMath::Abs(InnerRadius);

	if (RadiusMargin < 0.0f)
	{
		return false;
	}

	return FVector::DistSquared(OuterCenter, InnerCenter) <= RadiusMargin * RadiusMargin;
}


double UExtendedMathLibrary::AngleDistanceDegrees(double A, double B)
{
	A = FMath::Fmod(A, 360.0);
	B = FMath::Fmod(B, 360.0);

	double Delta = FMath::Abs(A - B);

	// Check Both ways
	Delta = FMath::Min(Delta, 360.0 - Delta);

	return Delta;
}

void UExtendedMathLibrary::GetAxisAndAngleBetweenRotators(const FRotator& A, const FRotator& B, FVector& Axis, double& Angle)
{
	FQuat QuatA = FQuat(A);
	FQuat QuatB = FQuat(B);

	// Calculate the shortest distance between quaternions
	FQuat DeltaQuat = QuatB.Inverse() * QuatA;

	// Convert the resulting quaternion to a rotation axis and angle
	double AngleRad;
	DeltaQuat.ToAxisAndAngle(Axis, AngleRad);

	Angle = FMath::RadiansToDegrees(AngleRad);
	//Angle = FMath::Min(Angle, 360.0 - Angle); // Normalize?

	//// Determine the sign of the angle
	//if (FVector::DotProduct(Axis, A.Vector()) < 0)
	//{
	//	Angle = -Angle;
	//}
}

void UExtendedMathLibrary::GetAxisAndAngleBetweenVectors(const FVector& A, const FVector& B, FVector& Axis, double& Angle)
{
	// Normalize both vectors
	FVector NormalizedVectorA = A.GetSafeNormal();
	FVector NormalizedVectorB = B.GetSafeNormal();

	// Calculate the dot product to get the cosine of the angle between them
	double DotProduct = FVector::DotProduct(NormalizedVectorA, NormalizedVectorB);

	// Clamp the dot product to [-1, 1] to avoid numerical errors
	DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);

	Axis = FVector::CrossProduct(NormalizedVectorA, NormalizedVectorB).GetSafeNormal();
	Angle = FMath::Acos(DotProduct);
}

double UExtendedMathLibrary::GetRotatorAngleRelativeToAxis(const FRotator Rotator, const FVector Axis)
{
	const FQuat Quaternion = FQuat(Rotator);
	const FVector NormalizedAxis = Axis.GetSafeNormal();

	if (NormalizedAxis.IsNearlyZero())
	{
		// Use relative up axis, or world up axis, or just return 0?
		//NormalizedAxis = FRotationMatrix(Rotator).GetScaledAxis(EAxis::Z); // Relative Up Vector.
		//NormalizedAxis = FVector(0, 0, 1); // World Up Vector.
		return 0;
	}

	const FQuat RotatedQuaternion = Quaternion * FQuat(0, NormalizedAxis.X, NormalizedAxis.Y, NormalizedAxis.Z) * Quaternion.Inverse();
	const double AngleRadians = FMath::Acos(RotatedQuaternion.W) * 2;
	return FMath::RadiansToDegrees(AngleRadians);
}


double UExtendedMathLibrary::Nearest(const double Reference, const double A, const double B)
{
	const double DifferenceA = FMath::Abs(Reference - A);
	const double DifferenceB = FMath::Abs(Reference - B);

	return DifferenceA < DifferenceB ? A : B;
}

double UExtendedMathLibrary::NearestAngle(const double ReferenceAngle, const double AngleA, const double AngleB, bool& bAIsNearest)
{
	const double DeltaA = FMath::FindDeltaAngleDegrees(AngleA, ReferenceAngle);
	const double DeltaB = FMath::FindDeltaAngleDegrees(AngleB, ReferenceAngle);
	bAIsNearest = FMath::Abs(DeltaA) < FMath::Abs(DeltaB);
	return bAIsNearest ? AngleA : AngleB;
}

double UExtendedMathLibrary::LerpAngleDegrees(double AngleA, double AngleB, double Alpha)
{
	AngleA = FMath::Fmod(AngleA, 360.0);
	AngleB = FMath::Fmod(AngleB, 360.0);

	double AngleDifference = AngleB - AngleA;

	// Ensure the shortest path between angles
	if (AngleDifference > 180.0)
	{
		AngleB -= 360.0;
	}
	else if (AngleDifference < -180.0)
	{
		AngleB += 360.0;
	}

	// Perform linear interpolation
	double LerpedAngle = AngleA + Alpha * (AngleB - AngleA);

	// Wrap angle within [0, 360) degrees
	LerpedAngle = FMath::Fmod(LerpedAngle, 360.0);
	if (LerpedAngle < 0)
	{
		LerpedAngle += 360.0;
	}

	return LerpedAngle;
}

FVector UExtendedMathLibrary::CalculateTriangleNormal(const FVector& Vertex1, const FVector& Vertex2, const FVector& Vertex3)
{
	const FVector Side1 = Vertex2 - Vertex1;
	const FVector Side2 = Vertex3 - Vertex1;
	return FVector::CrossProduct(Side1, Side2).GetSafeNormal();
}

FVector UExtendedMathLibrary::CalculateEdgeUpDirection(const FVector& Vertex1, const FVector& Vertex2)
{
	FVector EdgeVector = Vertex2 - Vertex1;
	return FVector::CrossProduct(EdgeVector, FVector::UpVector).GetSafeNormal();
}

int32 UExtendedMathLibrary::RandomWeightedArrayItem(const TArray<double>& WeightedArray)
{
	double TotalWeight = Algo::Accumulate(WeightedArray, 0.0);
	if (TotalWeight <= 0.0)
	{
		return INDEX_NONE;
	}
	
	double RandomPoint = FMath::FRandRange(0.0, TotalWeight);
	double AccumulatedWeight = 0.0;

	for (int32 i = 0; i < WeightedArray.Num(); ++i)
	{
		AccumulatedWeight += WeightedArray[i];
		if (RandomPoint <= AccumulatedWeight)
		{
			return i;
		}
	}

	// Fallback to last entry due to float rounding
	// Find the last non-zero entry.
	for (int i = WeightedArray.Num() - 1; i >= 0; --i)
	{
		if (WeightedArray[i] > 0.0)
		{
			return i;
		}
	}

	return INDEX_NONE; // This should never be reached as long as there was at least one non-zero weight.
}

int32 UExtendedMathLibrary::RandomWeightedArrayItemFromStream(const FRandomStream& Stream, const TArray<double>& WeightedArray)
{
	double TotalWeight = Algo::Accumulate(WeightedArray, 0.0);
	if (TotalWeight <= 0.0)
	{
		return INDEX_NONE;
	}

	double RandomPoint = Stream.FRandRange(0.0, TotalWeight);
	double AccumulatedWeight = 0.0;

	for (int32 i = 0; i < WeightedArray.Num(); ++i)
	{
		AccumulatedWeight += WeightedArray[i];
		if (RandomPoint <= AccumulatedWeight)
		{
			return i;
		}
	}

	// Fallback to last entry due to float rounding
	// Find the last non-zero entry.
	for (int i = WeightedArray.Num() - 1; i >= 0; --i)
	{
		if (WeightedArray[i] > 0.0)
		{
			return i;
		}
	}

	return INDEX_NONE; // This should never be reached as long as there was at least one non-zero weight.
}
