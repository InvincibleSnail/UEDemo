#include "UEDemoCharacter.h"
#include "UEDemoController.h"
#include "Input/PlayerInputConfigEvent.h"
#include "UInputComponentEx.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

AUEDemoCharacter::AUEDemoCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	FirstPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	FirstPersonCamera->bUsePawnControlRotation = true;
	
	WeaponComponent = ObjectInitializer.CreateDefaultSubobject<UWeaponComponent>(this, TEXT("WeaponComponent"));
}

void AUEDemoCharacter::BeginPlay()
{
	Super::BeginPlay();
	AueDemoController = Cast<AUEDemoController>(GetController());
	if (!AueDemoController)
	{
		return;
	}

	if (UInputComponentEx* InputEx = AueDemoController->GetInputComponentEx())
	{
		InputEx->RegisterInput(EPlayerInputConfigEvent::MoveForwardAxis, this, &AUEDemoCharacter::OnMoveForwardAxis);
		InputEx->RegisterInput(EPlayerInputConfigEvent::MoveRightAxis, this, &AUEDemoCharacter::OnMoveRightAxis);
		InputEx->RegisterInput(EPlayerInputConfigEvent::Look, this, &AUEDemoCharacter::OnLookAxis);
		InputEx->RegisterInput(EPlayerInputConfigEvent::Jump, this, &AUEDemoCharacter::OnJump);
	}
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

void AUEDemoCharacter::OnJump()
{
	Jump();
}
