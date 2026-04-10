#include "UEDemoController.h"

#include "CustomInputSubSystem.h"
#include "EnhancedInputSubsystems.h"
#include "UEDemoCharacter.h"

AUEDemoController::AUEDemoController(const FObjectInitializer& ObjectInitializer)
{
	InputComponentEx = ObjectInitializer.CreateDefaultSubobject<UInputComponentEx>(this, TEXT("InputComponentEx"));
	if (UInputComponentEx* IC = InputComponentEx)
	{
		if (auto* Subsystem = GetGameInstance()->GetSubsystem<UCustomInputSubSystem>())
		{
			IC->InputConfig = Subsystem->InputConfig;

			if (ULocalPlayer* LP = GetLocalPlayer())
			{
				if (auto* Subsys = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
				{
					Subsys->AddMappingContext(IC->InputConfig.DefaultMappingContext, 0);
				}
			}
		}
	}
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
