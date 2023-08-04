// Copyright 2023 Dream Seed LLC.


#include "ExtendedCurveLibrary.h"

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
