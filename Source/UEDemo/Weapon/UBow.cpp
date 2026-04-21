#include "UBow.h"

void UBow::Attack()
{
	Super::Attack();
}

bool UBow::CanAttack()
{
	return Super::CanAttack();
}

void UBow::SpawnAndAttachToCharacter(USkeletalMeshComponent* CharacterMesh)
{
	Super::SpawnAndAttachToCharacter(CharacterMesh);
}
