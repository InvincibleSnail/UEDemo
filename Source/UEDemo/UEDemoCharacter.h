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

	void WireInputWithController(APlayerController* PC);

	UInputComponentEx* GetInputComponentEx() const { return InputComponentEx; }

protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY()
	TObjectPtr<UInputComponentEx> InputComponentEx;

private:
	void BindInputDelegatesIfNeeded();

	void OnMoveForwardAxis(float Axis);
	void OnMoveRightAxis(float Axis);
	void OnLookAxis(const FVector2D& Axis);

	bool bInputGameplayDelegatesBound = false;
};
