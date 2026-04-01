#include "UEDemoCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "UEDemo.h"

AUEDemoCharacter::AUEDemoCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	MoveAction = NewObject<UInputAction>();
	MoveAction->ValueType = EInputActionValueType::Axis2D;
	MoveAction->AddToRoot();
}

void AUEDemoCharacter::BeginPlay()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			UInputMappingContext* IMC = NewObject<UInputMappingContext>(this);
			IMC->MapKey(MoveAction, EKeys::W);
			IMC->MapKey(MoveAction, EKeys::S);
			IMC->MapKey(MoveAction, EKeys::A);
			IMC->MapKey(MoveAction, EKeys::D);

			Subsystem->AddMappingContext(IMC, 0);
		}
	}
}

void AUEDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!enhancedInputComponent) return;
	if (MoveAction)
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Ongoing, this, &AUEDemoCharacter::Move);
}

void AUEDemoCharacter::Move(const FInputActionValue& Value)
{
	UE_LOG(LogUEDemo, Log, TEXT("Move Action!!!"));
	FVector2D V = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), V.Y);
	AddMovementInput(GetActorRightVector(), V.X);
}
