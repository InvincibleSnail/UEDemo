#include "UEDemoController.h"
#include "UEDemoCharacter.h"

AUEDemoController::AUEDemoController(const FObjectInitializer& ObjectInitializer)
{
	InputComponentEx = ObjectInitializer.CreateDefaultSubobject<UInputComponentEx>(this, TEXT("InputComponentEx"));
	if (InputComponentEx)
	{
		UInputAction* MoveForwardAction = ObjectInitializer.CreateDefaultSubobject<UInputAction>(
			this, TEXT("MoveForwardAction"));
		MoveForwardAction->ValueType = EInputActionValueType::Axis1D;

		UInputAction* MoveRightAction = ObjectInitializer.CreateDefaultSubobject<UInputAction>(
			this, TEXT("MoveRightAction"));
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
