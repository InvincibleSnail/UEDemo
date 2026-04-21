#include "UWeaponComponent.h"
#include "UWeaponBase.h"
#include "GameFramework/Character.h"

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	CreateWeapon();
}

void UWeaponComponent::EquipWeapon(TSubclassOf<UWeaponBase> NewWeaponClass)
{
	DefaultWeaponClass = NewWeaponClass;
	CreateWeapon();
}

void UWeaponComponent::Attack()
{
	if (CurrentWeapon)
		CurrentWeapon->Attack();
}

void UWeaponComponent::SwitchWeapon(TSubclassOf<UWeaponBase> NewWeaponClass)
{
	DefaultWeaponClass = NewWeaponClass;
	CreateWeapon();
}

UWeaponBase* UWeaponComponent::GetCurrentWeapon() const
{
	return CurrentWeapon;
}

bool UWeaponComponent::HasValidWeapon() const
{
	return CurrentWeapon != nullptr;
}

void UWeaponComponent::AttachWeaponToCharacter()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	USkeletalMeshComponent* characterMesh = Character->GetMesh();
	if (!characterMesh || !weaponMesh) return;

	UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(this);
	MeshComp->SetStaticMesh(weaponMesh);
	MeshComp->RegisterComponent();
	MeshComp->AttachToComponent(characterMesh, 
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		TEXT("hand_r")
	);
}

void UWeaponComponent::CreateWeapon()
{
	if (!DefaultWeaponClass)
		return;

	CurrentWeapon = NewObject<UWeaponBase>(this, DefaultWeaponClass);
	AttachWeaponToCharacter();
}

