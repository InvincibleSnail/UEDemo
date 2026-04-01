#include "UEDemoCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "GameFramework/PlayerController.h"
#include "UEDemo.h"

AUEDemoCharacter::AUEDemoCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	OverrideInputComponentClass = UEnhancedInputComponent::StaticClass();

	MoveForwardAction = ObjectInitializer.CreateDefaultSubobject<UInputAction>(this, TEXT("MoveForwardAction"));
	MoveForwardAction->ValueType = EInputActionValueType::Axis1D;

	MoveRightAction = ObjectInitializer.CreateDefaultSubobject<UInputAction>(this, TEXT("MoveRightAction"));
	MoveRightAction->ValueType = EInputActionValueType::Axis1D;
}

void AUEDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInput)
	{
		UE_LOG(LogUEDemo, Warning, TEXT("UEDemoCharacter: InputComponent is not UEnhancedInputComponent."));
		return;
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC || !PC->GetLocalPlayer())
	{
		UE_LOG(LogUEDemo, Warning, TEXT("UEDemoCharacter: No PlayerController or LocalPlayer during SetupPlayerInputComponent."));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem)
	{
		UE_LOG(LogUEDemo, Warning, TEXT("UEDemoCharacter: UEnhancedInputLocalPlayerSubsystem not found."));
		return;
	}

	if (!MoveMappingContext)
	{
		MoveMappingContext = NewObject<UInputMappingContext>(this, TEXT("MoveMappingContext"));

		MoveMappingContext->MapKey(MoveForwardAction, EKeys::W);
		{
			FEnhancedActionKeyMapping& MapS = MoveMappingContext->MapKey(MoveForwardAction, EKeys::S);
			UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(MoveMappingContext, TEXT("NegateForward"));
			MapS.Modifiers.Add(Negate);
		}

		MoveMappingContext->MapKey(MoveRightAction, EKeys::D);
		{
			FEnhancedActionKeyMapping& MapA = MoveMappingContext->MapKey(MoveRightAction, EKeys::A);
			UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(MoveMappingContext, TEXT("NegateRight"));
			MapA.Modifiers.Add(Negate);
		}
	}

	if (!bMoveMappingAdded)
	{
		Subsystem->AddMappingContext(MoveMappingContext, 0);
		bMoveMappingAdded = true;
	}

	EnhancedInput->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AUEDemoCharacter::OnMoveForward);
	EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AUEDemoCharacter::OnMoveRight);
}

void AUEDemoCharacter::OnMoveForward(const FInputActionValue& Value)
{
	const float Axis = Value.Get<float>();
	UE_LOG(LogUEDemo, Log, TEXT("MoveForward: %f"), Axis);
	AddMovementInput(GetActorForwardVector(), Axis);
}

void AUEDemoCharacter::OnMoveRight(const FInputActionValue& Value)
{
	const float Axis = Value.Get<float>();
	UE_LOG(LogUEDemo, Log, TEXT("MoveRight: %f"), Axis);
	AddMovementInput(GetActorRightVector(), Axis);
}
