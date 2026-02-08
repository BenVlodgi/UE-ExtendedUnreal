// Copyright 2025 Dream Seed LLC.

#pragma once

#include "Modules/ModuleManager.h"

class FExtendedUnrealUncookedOnlyModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
