#include "UEDemoCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Input/UInputComponentEx.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "GameFramework/PlayerController.h"
#include "UEDemo.h"

AUEDemoCharacter::AUEDemoCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	OverrideInputComponentClass = UEnhancedInputComponent::StaticClass();

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	FirstPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	InputComponentEx = ObjectInitializer.CreateDefaultSubobject<UInputComponentEx>(this, TEXT("InputComponentEx"));

	UInputAction* MoveForwardAction = ObjectInitializer.CreateDefaultSubobject<UInputAction>(this, TEXT("MoveForwardAction"));
	MoveForwardAction->ValueType = EInputActionValueType::Axis1D;

	UInputAction* MoveRightAction = ObjectInitializer.CreateDefaultSubobject<UInputAction>(this, TEXT("MoveRightAction"));
	MoveRightAction->ValueType = EInputActionValueType::Axis1D;

	UInputAction* LookAction = ObjectInitializer.CreateDefaultSubobject<UInputAction>(this, TEXT("LookAction"));
	LookAction->ValueType = EInputActionValueType::Axis2D;

	UInputMappingContext* MoveMappingContext = NewObject<UInputMappingContext>(this, TEXT("MoveMappingContext"));
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
	MoveMappingContext->MapKey(LookAction, EKeys::Mouse2D);

	InputComponentEx->InputConfig.MoveForwardAxis = MoveForwardAction;
	InputComponentEx->InputConfig.MoveRightAxis = MoveRightAction;
	InputComponentEx->InputConfig.Look = LookAction;
	InputComponentEx->InputConfig.DefaultMappingContext = MoveMappingContext;
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
	if (!PC)
	{
		UE_LOG(LogUEDemo, Warning, TEXT("UEDemoCharacter: No PlayerController during SetupPlayerInputComponent."));
		return;
	}

	if (!bInputExHooked)
	{
		InputComponentEx->OnMoveForwardAxis.AddUObject(this, &AUEDemoCharacter::OnMoveForwardAxis);
		InputComponentEx->OnMoveRightAxis.AddUObject(this, &AUEDemoCharacter::OnMoveRightAxis);
		InputComponentEx->OnLook.AddUObject(this, &AUEDemoCharacter::OnLookAxis);
		bInputExHooked = true;
	}

	InputComponentEx->InitializeInput(PC);
}

void AUEDemoCharacter::OnMoveForwardAxis(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

void AUEDemoCharacter::OnMoveRightAxis(float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis);
}

void AUEDemoCharacter::OnLookAxis(const FVector2D& Axis)
{
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(-Axis.Y);
}
