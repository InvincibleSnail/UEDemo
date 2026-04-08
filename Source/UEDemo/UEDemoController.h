#pragma once

#include "CoreMinimal.h"
#include "Input/UInputComponentEx.h"
#include "GameFramework/PlayerController.h"
#include "UEDemoController.generated.h"

class AUEDemoCharacter;

UCLASS()
class AUEDemoController : public APlayerController
{
	GENERATED_BODY()

public:
	AUEDemoController(const FObjectInitializer& ObjectInitializer);

	UInputComponentEx* GetInputComponentEx() const { return InputComponentEx; }

protected:
	UPROPERTY()
	TObjectPtr<UInputComponentEx> InputComponentEx;

	UPROPERTY()
	TObjectPtr<AUEDemoCharacter> AueDemoCharacter;
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
};
