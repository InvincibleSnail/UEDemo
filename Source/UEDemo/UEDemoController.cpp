#include "UEDemoController.h"

#include "CustomInputSubSystem.h"
#include "EnhancedInputSubsystems.h"
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

	if (!InputComponentEx)
	{
		return;
	}

	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCustomInputSubSystem* Subsystem = GI->GetSubsystem<UCustomInputSubSystem>())
		{
			InputComponentEx->InputConfig = Subsystem->InputConfig;
		}
	}

	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* EISubsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputComponentEx->InputConfig.DefaultMappingContext)
			{
				EISubsystem->AddMappingContext(InputComponentEx->InputConfig.DefaultMappingContext, 0);
			}
		}
	}

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
