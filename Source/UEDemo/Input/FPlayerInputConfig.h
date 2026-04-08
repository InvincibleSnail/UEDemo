#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "FPlayerInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInputConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Move")
	UInputAction* Move = nullptr;

	UPROPERTY(EditAnywhere, Category = "Move")
	UInputAction* MoveForwardAxis = nullptr;

	UPROPERTY(EditAnywhere, Category = "Move")
	UInputAction* MoveRightAxis = nullptr;

	UPROPERTY(EditAnywhere, Category = "Look")
	UInputAction* Look = nullptr;

	UPROPERTY(EditAnywhere, Category = "Jump")
	UInputAction* Jump = nullptr;

	UPROPERTY(EditAnywhere, Category = "PrimaryAttack")
	UInputAction* PrimaryAttack = nullptr;

	UPROPERTY(EditAnywhere, Category = "SecondaryAttack")
	UInputAction* SecondaryAttack = nullptr;

	UPROPERTY(EditAnywhere, Category = "SwitchWeapon")
	UInputAction* SwitchWeapon = nullptr;

	UPROPERTY(EditAnywhere, Category = "Context")
	UInputMappingContext* DefaultMappingContext = nullptr;
};
