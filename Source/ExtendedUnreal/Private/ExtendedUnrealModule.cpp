// Copyright 2023 Dream Seed LLC.

#include "ExtendedUnrealModule.h"

#include "ExtendedUnrealLog.h"
DEFINE_LOG_CATEGORY(LogExtendedUnreal);

#define LOCTEXT_NAMESPACE "FExtendedUnrealModule"

void FExtendedUnrealModule::StartupModule()
{
}

void FExtendedUnrealModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExtendedUnrealModule, ExtendedUnreal)