// Copyright 2023 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"


#include "ExtendedCurveLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedCurveLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Evaluate this float curve at the specified time */
	UFUNCTION(BlueprintCallable, meta = (DisplayName="Get Float Value", Category="Math|Curves"))
	static float RuntimeFloatCurveValue(const FRuntimeFloatCurve& Curve, double InTime);

	/** Get range of input time values. Outside this region curve continues constantly the start/end values. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Time Range", Category = "Math|Curves"))
	static void RuntimeFloatCurveTimeRange(const FRuntimeFloatCurve& Curve, float& MinTime, float& MaxTime);

	/** Get range of output values. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Value Range", Category = "Math|Curves"))
	static void RuntimeFloatCurveValueRange(const FRuntimeFloatCurve& Curve, float& MinValue, float& MaxValue);

	/** Returns whether the curve is constant or not */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Constant", Category = "Math|Curves"))
	static void RuntimeFloatCurveIsConstant(const FRuntimeFloatCurve& Curve, bool& IsConstant);

	/** Returns whether the curve is empty or not */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Empty", Category = "Math|Curves"))
	static void RuntimeFloatCurveIsEmpty(const FRuntimeFloatCurve& Curve, bool& IsEmpty);

	/** 
	 * Returns Curve Float object. 
	 * If using External Curve: that will be returned.
	 * Else a new curve object will be created with the curve data.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Curve", Category = "Math|Curves"))
	static UPARAM(DisplayName = "Float Curve") UCurveFloat* RuntimeFloatCurve_GetCurve(const FRuntimeFloatCurve& Curve);

	/**
	 * Returns Curve Vector object.
	 * If using External Curve: that will be returned.
	 * Else a new curve object will be created with the curve data.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Curve", Category = "Math|Curves"))
	static UPARAM(DisplayName = "Vector Curve") UCurveVector* RuntimeVectorCurve_GetCurve(const FRuntimeVectorCurve& Curve);

};
