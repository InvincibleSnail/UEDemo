// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEDemoCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "UEDemo.h"

AUEDemoCharacter::AUEDemoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AUEDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 传统输入：由 Config/DefaultInput.ini 的 AxisMappings / ActionMappings 提供（不依赖 Content 里的 Enhanced Input 资产）
	PlayerInputComponent->BindAxis(FName(TEXT("MoveForward")), this, &AUEDemoCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName(TEXT("MoveRight")), this, &AUEDemoCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName(TEXT("Turn")), this, &AUEDemoCharacter::Turn);
	PlayerInputComponent->BindAxis(FName(TEXT("LookUp")), this, &AUEDemoCharacter::LookUp);
	PlayerInputComponent->BindAction(FName(TEXT("Jump")), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName(TEXT("Jump")), IE_Released, this, &ACharacter::StopJumping);
}

void AUEDemoCharacter::MoveForward(float Value)
{
	MoveForwardAxis = Value;
	DoMove(MoveRightAxis, MoveForwardAxis);
}

void AUEDemoCharacter::MoveRight(float Value)
{
	MoveRightAxis = Value;
	DoMove(MoveRightAxis, MoveForwardAxis);
}

void AUEDemoCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AUEDemoCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AUEDemoCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AUEDemoCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AUEDemoCharacter::DoJumpStart()
{
	Jump();
}

void AUEDemoCharacter::DoJumpEnd()
{
	StopJumping();
}
