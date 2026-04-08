#pragma once

#include "CoreMinimal.h"

enum class EPlayerInputConfigEvent : uint8
{
	Move,
	MoveForwardAxis,
	MoveRightAxis,
	Look,
	Jump,
	PrimaryAttack,
	SecondaryAttack,
	SwitchWeapon,
};
