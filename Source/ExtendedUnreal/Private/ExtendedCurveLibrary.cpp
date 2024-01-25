// Copyright 2024 Dream Seed LLC.


#include "ExtendedCurveLibrary.h"


#include "Curves/CurveVector.h"

float UExtendedCurveLibrary::RuntimeFloatCurveValue(const FRuntimeFloatCurve& Curve, double InTime)
{
	const FRichCurve* RichCurve = Curve.GetRichCurveConst();
	return RichCurve ? RichCurve->Eval((float)InTime) : 0.0f;
}

void UExtendedCurveLibrary::RuntimeFloatCurveTimeRange(const FRuntimeFloatCurve& Curve, float& MinTime, float& MaxTime)
{
	const FRichCurve* RichCurve = Curve.GetRichCurveConst();
	if (RichCurve)
	{
		RichCurve->GetTimeRange(MinTime, MaxTime);
	}
	else
	{
		MinTime = 0.0f;
		MaxTime = 0.0f;
	}
}

void UExtendedCurveLibrary::RuntimeFloatCurveValueRange(const FRuntimeFloatCurve& Curve, float& MinValue, float& MaxValue)
{
	const FRichCurve* RichCurve = Curve.GetRichCurveConst();
	if (RichCurve)
	{
		RichCurve->GetValueRange(MinValue, MaxValue);
	}
	else
	{
		MinValue = 0.0f;
		MaxValue = 0.0f;
	}
}

void UExtendedCurveLibrary::RuntimeFloatCurveIsConstant(const FRuntimeFloatCurve& Curve, bool& IsConstant)
{
	if (const FRichCurve* RichCurve = Curve.GetRichCurveConst())
		IsConstant = RichCurve->IsConstant();
	else
		IsConstant = false;
}

void UExtendedCurveLibrary::RuntimeFloatCurveIsEmpty(const FRuntimeFloatCurve& Curve, bool& IsEmpty)
{
	if (const FRichCurve* RichCurve = Curve.GetRichCurveConst())
		IsEmpty = RichCurve->IsEmpty();
	else
		IsEmpty = true;
}

UCurveFloat* UExtendedCurveLibrary::RuntimeFloatCurve_GetCurve(const FRuntimeFloatCurve& Curve)
{
	if (Curve.ExternalCurve)
	{
		return Curve.ExternalCurve;
	}
	else
	{
		UCurveFloat* NewCurve = NewObject<UCurveFloat>();
		NewCurve->FloatCurve = *Curve.GetRichCurveConst();
		return NewCurve;
	}
}

UCurveVector* UExtendedCurveLibrary::RuntimeVectorCurve_GetCurve(const FRuntimeVectorCurve& Curve)
{
	if (Curve.ExternalCurve)
	{
		return Curve.ExternalCurve;
	}
	else
	{
		UCurveVector* NewCurve = NewObject<UCurveVector>();
		NewCurve->FloatCurves[0] = *Curve.GetRichCurveConst(0);
		NewCurve->FloatCurves[1] = *Curve.GetRichCurveConst(1);
		NewCurve->FloatCurves[2] = *Curve.GetRichCurveConst(2);
		return NewCurve;
	}
}
