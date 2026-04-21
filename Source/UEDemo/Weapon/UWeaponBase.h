#pragma once
#include "UWeaponBase.generated.h"

UCLASS()
class UWeaponBase : public UObject
{
	GENERATED_BODY()

public:
	UWeaponBase();
	virtual void Attack();
	virtual bool CanAttack();
	virtual void SpawnAndAttachToCharacter(USkeletalMeshComponent* CharacterMesh);
	UPROPERTY(EditAnywhere, Category="Weapon")
	UStaticMesh* WeaponMesh;
protected:
	UPROPERTY()
	float Damage = 10.0f;
	UPROPERTY()
	float CoolDown = 0.5f;
};
