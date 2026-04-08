#include "UEDemoController.h"
#include "UEDemoCharacter.h"

void AUEDemoController::BeginPlay()
{
	Super::BeginPlay();
	TryWirePawnInput();
}

void AUEDemoController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	TryWirePawnInput();
}

void AUEDemoController::TryWirePawnInput()
{
	AUEDemoCharacter* Char = Cast<AUEDemoCharacter>(GetPawn());
	if (!Char)
	{
		return;
	}

	Char->WireInputWithController(this);
}
