#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UEDemoCharacter.generated.h"

class UCameraComponent;
class AUEDemoController;

UCLASS()
class AUEDemoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUEDemoCharacter(const FObjectInitializer& ObjectInitializer);
	
protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> FirstPersonCamera;
	UPROPERTY()
	AUEDemoController* AueDemoController;
	
	virtual void BeginPlay() override;

private:
	void OnMoveForwardAxis(float Axis);
	void OnMoveRightAxis(float Axis);
	void OnLookAxis(const FVector2D& Axis);
};
