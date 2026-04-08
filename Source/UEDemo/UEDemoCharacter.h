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

	/** 由 AUEDemoController::OnPossess 调用：绑定 Input 委托到本角色并 Initialize Enhanced Input */
	void WireInputWithController(class APlayerController* PC);

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
