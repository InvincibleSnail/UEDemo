#include "UEDemoGameMode.h"
#include "UEDemoCharacter.h"
#include "UEDemoController.h"

AUEDemoGameMode::AUEDemoGameMode()
{
	DefaultPawnClass = AUEDemoCharacter::StaticClass();
	PlayerControllerClass = AUEDemoController::StaticClass();
}
