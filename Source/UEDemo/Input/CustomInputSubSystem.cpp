#include "CustomInputSubSystem.h"
#include "InputModifiers.h"

void UCustomInputSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InitInputActions();
	InitMappingContext();
}

void UCustomInputSubSystem::InitInputActions()
{
	InputConfig.MoveForwardAxis = NewObject<UInputAction>(this);
	InputConfig.MoveForwardAxis->ValueType = EInputActionValueType::Axis1D;

	InputConfig.MoveRightAxis = NewObject<UInputAction>(this);
	InputConfig.MoveRightAxis->ValueType = EInputActionValueType::Axis1D;

	InputConfig.Look = NewObject<UInputAction>(this);
	InputConfig.Look->ValueType = EInputActionValueType::Axis2D;
}

void UCustomInputSubSystem::InitMappingContext()
{
	InputConfig.DefaultMappingContext = NewObject<UInputMappingContext>(this);

	InputConfig.DefaultMappingContext->MapKey(InputConfig.MoveForwardAxis, EKeys::W);

	auto& MapS = InputConfig.DefaultMappingContext->MapKey(InputConfig.MoveForwardAxis, EKeys::S);
	auto NegateS = NewObject<UInputModifierNegate>();
	MapS.Modifiers.Add(NegateS);

	InputConfig.DefaultMappingContext->MapKey(InputConfig.MoveRightAxis, EKeys::D);

	auto& MapA = InputConfig.DefaultMappingContext->MapKey(InputConfig.MoveRightAxis, EKeys::A);
	auto NegateA = NewObject<UInputModifierNegate>();
	MapA.Modifiers.Add(NegateA);

	InputConfig.DefaultMappingContext->MapKey(InputConfig.Look, EKeys::Mouse2D);
}