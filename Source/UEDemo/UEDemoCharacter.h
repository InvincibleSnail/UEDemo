#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UEDemoCharacter.generated.h"

class UCameraComponent;
class UInputComponentEx;

UCLASS()
class AUEDemoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUEDemoCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY()
	TObjectPtr<UInputComponentEx> InputComponentEx;

private:
	void OnMoveForwardAxis(float Axis);
	void OnMoveRightAxis(float Axis);
	void OnLookAxis(const FVector2D& Axis);

	bool bInputExHooked = false;
};
