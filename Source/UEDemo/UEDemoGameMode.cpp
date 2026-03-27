#include "UEDemoGameMode.h"
#include "UEDemoPawn.h"
#include "UEDemoController.h"

AUEDemoGameMode::AUEDemoGameMode()
{
	DefaultPawnClass = AUEDemoPawn::StaticClass();
	PlayerControllerClass = AUEDemoController::StaticClass();
}
