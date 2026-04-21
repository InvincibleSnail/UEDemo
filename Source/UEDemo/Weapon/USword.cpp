#include "USword.h"

void USword::Attack()
{
	Super::Attack();
}

bool USword::CanAttack()
{
	return Super::CanAttack();
}

void USword::SpawnAndAttachToCharacter(USkeletalMeshComponent* CharacterMesh)
{
	Super::SpawnAndAttachToCharacter(CharacterMesh);
	if (!CharacterMesh || !WeaponMesh) return;

	UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(this);
	MeshComp->SetStaticMesh(WeaponMesh);
	MeshComp->RegisterComponent();
	MeshComp->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("hand_r")
	);
}
