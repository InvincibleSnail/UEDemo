#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UEDemoGameMode.generated.h"

class UUserWidget;

UCLASS()
class UEDEMO_API AUEDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUEDemoGameMode();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> StartupWidgetClass;
};
