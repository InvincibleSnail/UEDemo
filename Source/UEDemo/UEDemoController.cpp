#include "UEDemoController.h"
#include "Blueprint/UserWidget.h"

void AUEDemoController::BeginPlay()
{
	Super::BeginPlay();
	
	if (LoginUIClass)
	{
		LoginUIInstance = CreateWidget<UUserWidget>(this, LoginUIClass);
		if (LoginUIInstance)
		{
			LoginUIInstance->AddToViewport();
			bShowMouseCursor = true;
		}
	}
}