// Copyright 2023 Dream Seed LLC.


#include "ExtendedAnimationLibrary.h"


#include "Animation/BlendSpace.h"

void UExtendedAnimationLibrary::GetBlendSpaceAxisMinMax(UBlendSpace* BlendSpace, EExtendedBlendSpaceAxis Axis, double& Min, double& Max)
{
	FBlendParameter BlendParameter = BlendSpace->GetBlendParameter((int)Axis);
	Min = BlendParameter.Min;
	Max = BlendParameter.Max;
}
