// Copyright Epic Games, Inc. All Rights Reserved.


#include "UEDemoPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UEDemo.h"
#include "Widgets/Input/SVirtualJoystick.h"

void AUEDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogUEDemo, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AUEDemoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// 无 Content 时由 DefaultInput.ini + 传统 PlayerInput 驱动；若以后加回 Enhanced Input IMC，可在此处 AddMappingContext
}

bool AUEDemoPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}
