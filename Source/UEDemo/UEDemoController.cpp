#include "UEDemoController.h"
#include "UEDemoCharacter.h"

AUEDemoController::AUEDemoController(const FObjectInitializer& ObjectInitializer)
{
	InputComponentEx = ObjectInitializer.CreateDefaultSubobject<UInputComponentEx>(this, TEXT("InputComponentEx"));
}

UInputComponentEx* AUEDemoController::GetInputComponentEx() const
{
	return InputComponentEx;
}

void AUEDemoController::BeginPlay()
{
	Super::BeginPlay();
	InputComponentEx->InitializeInput(this);
}

void AUEDemoController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AUEDemoCharacter* CastedCharacter = Cast<AUEDemoCharacter>(InPawn);

	if (CastedCharacter)
	{
		AueDemoCharacter = CastedCharacter;
	}
}
