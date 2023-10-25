// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEntropyLatentModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

#include "EntropyLatent_Delay.h"
#include "EntropyLatent_DelayTicks.h"
#include "EntropyLatent_ExecuteOnThread.h"
