#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UEDemoController.generated.h"

UCLASS()
class AUEDemoController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	void TryWirePawnInput();
};
