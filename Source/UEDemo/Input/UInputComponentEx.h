#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "FPlayerInputConfig.h"
#include "UInputComponentEx.generated.h"

class UEnhancedInputComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UEDEMO_API UInputComponentEx : public UActorComponent
{
	GENERATED_BODY()

public:
	UInputComponentEx();

	UPROPERTY(EditAnywhere, Category = "Input Setup")
	FPlayerInputConfig InputConfig;

	void InitializeInput(APlayerController* PlayerController);

	DECLARE_MULTICAST_DELEGATE_OneParam(FInputAxis2D, const FVector2D&);
	DECLARE_MULTICAST_DELEGATE(FInputAction);

	FInputAxis2D OnMove;
	FInputAxis2D OnLook;
	FInputAction OnJump;
	FInputAction OnPrimaryAttack;
	FInputAction OnSecondaryAttack;
	FInputAction OnSwitchWeapon;

private:
	void AddMappingContext(APlayerController* PlayerController);
	void BindActions(UEnhancedInputComponent* EnhancedInputComponent);

	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleJump(const FInputActionValue& Value);
	void HandlePrimaryAttack(const FInputActionValue& Value);
	void HandleSecondaryAttack(const FInputActionValue& Value);
	void HandleSwitchWeapon(const FInputActionValue& Value);
};
