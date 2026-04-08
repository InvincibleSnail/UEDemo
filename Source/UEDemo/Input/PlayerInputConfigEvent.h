#pragma once

#include "CoreMinimal.h"

/** 与 FPlayerInputConfig 里每个 UInputAction* 字段一一对应，用于按“槽位”注册回调。 */
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
