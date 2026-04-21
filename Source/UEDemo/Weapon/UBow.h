#pragma once
#include "UWeaponBase.h"
#include "UBow.generated.h"

UCLASS()
class UBow : public UWeaponBase
{
	GENERATED_BODY()
public:
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void SpawnAndAttachToCharacter(USkeletalMeshComponent* CharacterMesh) override;
};
