#include "UEDemoGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UEDemoCharacter.h"
#include "UEDemoController.h"
#include "UEDemo.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
	static constexpr TCHAR LoginUIWidgetPath[] = TEXT("/Game/Blueprint/UI/LoginUI.LoginUI_C");
}

AUEDemoGameMode::AUEDemoGameMode()
{
	DefaultPawnClass = AUEDemoCharacter::StaticClass();
	PlayerControllerClass = AUEDemoController::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> LoginUIClassFinder(LoginUIWidgetPath);
	if (LoginUIClassFinder.Succeeded())
	{
		StartupWidgetClass = LoginUIClassFinder.Class;
	}
	else
	{
		UE_LOG(LogUEDemo, Warning, TEXT("Failed to load Login UI widget at %s — create the asset or fix the path."), LoginUIWidgetPath);
	}
}
