// Copyright 2023 Dream Seed LLC.


#include "ExtendedMathLibrary.h"

#include "Math/Vector.h"
#include "Math/Plane.h"

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
