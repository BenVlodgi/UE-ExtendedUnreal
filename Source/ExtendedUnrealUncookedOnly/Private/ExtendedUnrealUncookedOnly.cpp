// Copyright 2025 Dream Seed LLC.

#include "ExtendedUnrealUncookedOnly.h"

static const FName DynamicSaveUncookedOnlyTabName("ExtendedUnrealUncookedOnly");

#define LOCTEXT_NAMESPACE "FExtendedUnrealUncookedOnlyModule"

void FExtendedUnrealUncookedOnlyModule::StartupModule()
{
}

void FExtendedUnrealUncookedOnlyModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExtendedUnrealUncookedOnlyModule, ExtendedUnrealUncookedOnly)