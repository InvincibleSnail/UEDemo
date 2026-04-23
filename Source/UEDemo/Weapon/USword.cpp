#include "USword.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/UObjectGlobals.h"

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
	if (!CharacterMesh) return;

	UStaticMesh* MeshToUse = WeaponMesh;
	if (!MeshToUse)
	{
		MeshToUse = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	}
	if (!MeshToUse) return;

	AActor* OwnerActor = CharacterMesh->GetOwner();
	if (!OwnerActor) return;

	const FName HandSocket(TEXT("hand_r"));
	const FName AttachSocket = CharacterMesh->DoesSocketExist(HandSocket) ? HandSocket : NAME_None;

	UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(OwnerActor, NAME_None, RF_Transient);
	MeshComp->SetStaticMesh(MeshToUse);
	MeshComp->SetMobility(EComponentMobility::Movable);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OwnerActor->AddInstanceComponent(MeshComp);
	MeshComp->RegisterComponent();
	MeshComp->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocket);
}
