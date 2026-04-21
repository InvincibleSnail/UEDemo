#pragma once
#include "UWeaponBase.h"
#include "USword.generated.h"

UCLASS()
class USword : public UWeaponBase
{
	GENERATED_BODY()
public:
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void SpawnAndAttachToCharacter(USkeletalMeshComponent* CharacterMesh) override;
};
