// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEDemoGameMode.h"
#include "UEDemoCharacter.h"
#include "UEDemoPlayerController.h"

AUEDemoGameMode::AUEDemoGameMode()
{
	DefaultPawnClass = AUEDemoCharacter::StaticClass();
	PlayerControllerClass = AUEDemoPlayerController::StaticClass();
}
