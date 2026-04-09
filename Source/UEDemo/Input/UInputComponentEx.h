#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "FPlayerInputConfig.h"
#include "PlayerInputConfigEvent.h"
#include "UInputComponentEx.generated.h"

class UEnhancedInputComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UEDEMO_API UInputComponentEx : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Input Setup")
	FPlayerInputConfig InputConfig;
	
	UInputComponentEx();
	void InitializeInput(APlayerController* PlayerController);
	template<typename U>
	void RegisterInput(EPlayerInputConfigEvent Slot, U* User, void (U::*Handler)(float));
	template<typename U>
	void RegisterInput(EPlayerInputConfigEvent Slot, U* User, void (U::*Handler)(const FVector2D&));
	template<typename U>
	void RegisterInput(EPlayerInputConfigEvent Slot, U* User, void (U::*Handler)());

	DECLARE_MULTICAST_DELEGATE_OneParam(FInputAxis2D, const FVector2D&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FInputAxis1D, float);
	DECLARE_MULTICAST_DELEGATE(FInputAction);

	FInputAxis2D OnMove;
	FInputAxis1D OnMoveForwardAxis;
	FInputAxis1D OnMoveRightAxis;
	FInputAxis2D OnLook;
	FInputAction OnJump;
	FInputAction OnPrimaryAttack;
	FInputAction OnSecondaryAttack;
	FInputAction OnSwitchWeapon;

private:
	void AddMappingContext(APlayerController* PlayerController);
	void BindActions(UEnhancedInputComponent* EnhancedInputComponent);

	void HandleMove(const FInputActionValue& Value);
	void HandleMoveForwardAxis(const FInputActionValue& Value);
	void HandleMoveRightAxis(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleJump(const FInputActionValue& Value);
	void HandlePrimaryAttack(const FInputActionValue& Value);
	void HandleSecondaryAttack(const FInputActionValue& Value);
	void HandleSwitchWeapon(const FInputActionValue& Value);

	bool bDefaultMappingPushed = false;
	bool bActionsBound = false;
};

template<typename U>
void UInputComponentEx::RegisterInput(EPlayerInputConfigEvent Slot, U* User, void (U::*Handler)(float))
{
	switch (Slot)
	{
	case EPlayerInputConfigEvent::MoveForwardAxis:
		OnMoveForwardAxis.AddUObject(User, Handler);
		break;
	case EPlayerInputConfigEvent::MoveRightAxis:
		OnMoveRightAxis.AddUObject(User, Handler);
		break;
	default:
		checkNoEntry();
		break;
	}
}

template<typename U>
void UInputComponentEx::RegisterInput(EPlayerInputConfigEvent Slot, U* User, void (U::*Handler)(const FVector2D&))
{
	switch (Slot)
	{
	case EPlayerInputConfigEvent::Move:
		OnMove.AddUObject(User, Handler);
		break;
	case EPlayerInputConfigEvent::Look:
		OnLook.AddUObject(User, Handler);
		break;
	default:
		checkNoEntry();
		break;
	}
}

template<typename U>
void UInputComponentEx::RegisterInput(EPlayerInputConfigEvent Slot, U* User, void (U::*Handler)())
{
	switch (Slot)
	{
	case EPlayerInputConfigEvent::Jump:
		OnJump.AddUObject(User, Handler);
		break;
	case EPlayerInputConfigEvent::PrimaryAttack:
		OnPrimaryAttack.AddUObject(User, Handler);
		break;
	case EPlayerInputConfigEvent::SecondaryAttack:
		OnSecondaryAttack.AddUObject(User, Handler);
		break;
	case EPlayerInputConfigEvent::SwitchWeapon:
		OnSwitchWeapon.AddUObject(User, Handler);
		break;
	default:
		checkNoEntry();
		break;
	}
}
