// Copyright 2023 Dream Seed LLC.

#pragma once

#include "Modules/ModuleManager.h"

class FExtendedUnrealModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
