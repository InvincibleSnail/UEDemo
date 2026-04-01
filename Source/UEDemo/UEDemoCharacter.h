#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UEDemoCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class AUEDemoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUEDemoCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnMoveForward(const struct FInputActionValue& Value);
	void OnMoveRight(const struct FInputActionValue& Value);

	UPROPERTY()
	TObjectPtr<UInputAction> MoveForwardAction;

	UPROPERTY()
	TObjectPtr<UInputAction> MoveRightAction;

	UPROPERTY()
	TObjectPtr<UInputMappingContext> MoveMappingContext;

	bool bMoveMappingAdded = false;
};
