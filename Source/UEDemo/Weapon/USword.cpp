#include "USword.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

USword::USword()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMeshFinder(
		TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (WeaponMeshFinder.Succeeded())
	{
		WeaponMesh = WeaponMeshFinder.Object;
	}
}

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

	AActor* OwnerActor = CharacterMesh->GetOwner();
	if (!OwnerActor) return;

	const FName HandSocket(TEXT("hand_r"));
	const FName AttachSocket = CharacterMesh->DoesSocketExist(HandSocket) ? HandSocket : NAME_None;

	UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(OwnerActor);
	MeshComp->SetStaticMesh(WeaponMesh);
	MeshComp->RegisterComponent();
	MeshComp->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocket);
}
