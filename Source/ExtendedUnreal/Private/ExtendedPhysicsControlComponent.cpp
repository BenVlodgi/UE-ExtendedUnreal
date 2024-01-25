// Copyright 


#include "ExtendedPhysicsControlComponent.h"


#include "PhysicsEngine/ConstraintInstance.h"

//void UExtendedPhysicsControlComponent::ToggleZAxisForce(FName ControlName)
//{
//	//FPhysicsControlRecord* RecordPtr = Implementation->PhysicsControlRecords.Find(ControlName);
//	//if(RecordPtr)
//	//{
//	//	FConstraintInstance* ConstraintInstance = RecordPtr->PhysicsControlState.ConstraintInstance.Get();
//	//}
//}

void UExtendedPhysicsControlComponent::ToggleControlZAxisForce(FName Name)
{
	FConstraintInstance* ConstraintInstance = GetControlConstraintInstance(Name).Get();
	if (ConstraintInstance)
	{
		ConstraintInstance->SetLinearPositionDrive(true, true, false);
	}
}
