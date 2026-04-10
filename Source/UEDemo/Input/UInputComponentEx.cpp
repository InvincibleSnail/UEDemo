#include "UInputComponentEx.h"

#include "CustomInputSubSystem.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

UInputComponentEx::UInputComponentEx()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInputComponentEx::OnRegister()
{
	Super::OnRegister();

	if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
	{
		if (UGameInstance* GI = PC->GetGameInstance())
		{
			if (UCustomInputSubSystem* Subsystem = GI->GetSubsystem<UCustomInputSubSystem>())
			{
				InputConfig = Subsystem->InputConfig;
			}
		}
	}
}

void UInputComponentEx::InitializeInput(APlayerController* PlayerController)
{
	if (!PlayerController)
	{
		return;
	}

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
	{
		BindActions(EIC);
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
