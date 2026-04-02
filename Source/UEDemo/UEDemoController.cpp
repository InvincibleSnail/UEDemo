#include "UEDemoController.h"
#include "Blueprint/UserWidget.h"
#include "UEDemoGameMode.h"

void AUEDemoController::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<UUserWidget> WidgetClass;
	if (AUEDemoGameMode* DemoGM = GetWorld() ? Cast<AUEDemoGameMode>(GetWorld()->GetAuthGameMode()) : nullptr)
	{
		WidgetClass = DemoGM->StartupWidgetClass;
	}
	if (!WidgetClass)
	{
		WidgetClass = LoginUIClass;
	}

	if (!WidgetClass)
	{
		return;
	}

	LoginUIInstance = CreateWidget<UUserWidget>(this, WidgetClass);
	if (!LoginUIInstance)
	{
		return;
	}

	LoginUIInstance->AddToViewport();

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
	SetIgnoreLookInput(true);
}