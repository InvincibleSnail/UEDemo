#include "UEDemoCharacter.h"

#include "UEDemo.h"

AUEDemoCharacter::AUEDemoCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	MoveAction = NewObject<UInputAction>();
	MoveAction->AddToRoot();
}

void AUEDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (enhancedInputComponent && MoveAction)
	{
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUEDemoCharacter::Move);
	}
}

void AUEDemoCharacter::Move()
{
	UE_LOG(LogUEDemo, Log, TEXT("Move Action!!!"));
}
