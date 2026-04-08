#include "UInputComponentEx.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

UInputComponentEx::UInputComponentEx()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInputComponentEx::InitializeInput(APlayerController* PlayerController)
{
	if (!PlayerController)
	{
		return;
	}

	AddMappingContext(PlayerController);

	APawn* Pawn = PlayerController->GetPawn();
	if (!Pawn)
	{
		return;
	}

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(Pawn->InputComponent))
	{
		BindActions(EIC);
	}
}

void UInputComponentEx::AddMappingContext(APlayerController* PlayerController)
{
	if (!InputConfig.DefaultMappingContext)
	{
		return;
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		return;
	}

	if (bDefaultMappingPushed)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsys = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsys->AddMappingContext(InputConfig.DefaultMappingContext, 0);
		bDefaultMappingPushed = true;
	}
}

void UInputComponentEx::BindActions(UEnhancedInputComponent* EnhancedInput)
{
	if (!EnhancedInput)
	{
		return;
	}

	if (bActionsBound)
	{
		return;
	}

	if (InputConfig.MoveForwardAxis)
	{
		EnhancedInput->BindAction(InputConfig.MoveForwardAxis, ETriggerEvent::Triggered, this, &UInputComponentEx::HandleMoveForwardAxis);
	}
	if (InputConfig.MoveRightAxis)
	{
		EnhancedInput->BindAction(InputConfig.MoveRightAxis, ETriggerEvent::Triggered, this, &UInputComponentEx::HandleMoveRightAxis);
	}
	if (InputConfig.Move)
	{
		EnhancedInput->BindAction(InputConfig.Move, ETriggerEvent::Triggered, this, &UInputComponentEx::HandleMove);
	}
	if (InputConfig.Look)
	{
		EnhancedInput->BindAction(InputConfig.Look, ETriggerEvent::Triggered, this, &UInputComponentEx::HandleLook);
	}
	if (InputConfig.Jump)
	{
		EnhancedInput->BindAction(InputConfig.Jump, ETriggerEvent::Started, this, &UInputComponentEx::HandleJump);
	}
	if (InputConfig.PrimaryAttack)
	{
		EnhancedInput->BindAction(InputConfig.PrimaryAttack, ETriggerEvent::Started, this, &UInputComponentEx::HandlePrimaryAttack);
	}
	if (InputConfig.SecondaryAttack)
	{
		EnhancedInput->BindAction(InputConfig.SecondaryAttack, ETriggerEvent::Started, this, &UInputComponentEx::HandleSecondaryAttack);
	}
	if (InputConfig.SwitchWeapon)
	{
		EnhancedInput->BindAction(InputConfig.SwitchWeapon, ETriggerEvent::Started, this, &UInputComponentEx::HandleSwitchWeapon);
	}

	bActionsBound = true;
}

void UInputComponentEx::HandleMove(const FInputActionValue& Value)
{
	OnMove.Broadcast(Value.Get<FVector2D>());
}

void UInputComponentEx::HandleMoveForwardAxis(const FInputActionValue& Value)
{
	OnMoveForwardAxis.Broadcast(Value.Get<float>());
}

void UInputComponentEx::HandleMoveRightAxis(const FInputActionValue& Value)
{
	OnMoveRightAxis.Broadcast(Value.Get<float>());
}

void UInputComponentEx::HandleLook(const FInputActionValue& Value)
{
	OnLook.Broadcast(Value.Get<FVector2D>());
}

void UInputComponentEx::HandleJump(const FInputActionValue& Value)
{
	(void)Value;
	OnJump.Broadcast();
}

void UInputComponentEx::HandlePrimaryAttack(const FInputActionValue& Value)
{
	(void)Value;
	OnPrimaryAttack.Broadcast();
}

void UInputComponentEx::HandleSecondaryAttack(const FInputActionValue& Value)
{
	(void)Value;
	OnSecondaryAttack.Broadcast();
}

void UInputComponentEx::HandleSwitchWeapon(const FInputActionValue& Value)
{
	(void)Value;
	OnSwitchWeapon.Broadcast();
}
