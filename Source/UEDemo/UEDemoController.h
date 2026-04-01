#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/PlayerController.h"
#include "UEDemoController.generated.h"

class UUserWidget;

UCLASS()
class AUEDemoController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> LoginUIClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> LoginUIInstance;
};