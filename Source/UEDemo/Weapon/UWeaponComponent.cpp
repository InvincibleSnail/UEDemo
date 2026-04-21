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
	if (!Character || !CurrentWeapon) return;

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	if (!CharacterMesh) return;

	CurrentWeapon->SpawnAndAttachToCharacter(CharacterMesh);
}

void UWeaponComponent::CreateWeapon()
{
	if (!DefaultWeaponClass)
		return;

	CurrentWeapon = NewObject<UWeaponBase>(this, DefaultWeaponClass);
	AttachWeaponToCharacter();
}

