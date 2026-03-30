#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "UEDemoCharacter.generated.h"

UCLASS()
class AUEDemoCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UInputAction* MoveAction;
	void Move();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
public:
	AUEDemoCharacter();
};
