#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UWeaponBase.h"
#include "UWeaponComponent.generated.h"

UCLASS()
class UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	void EquipWeapon(TSubclassOf<UWeaponBase> NewWeaponClass);
	void Attack();
	void SwitchWeapon(TSubclassOf<UWeaponBase> NewWeaponClass);
	UWeaponBase* GetCurrentWeapon() const;
	bool HasValidWeapon() const;
private:
	void CreateWeapon();
	UPROPERTY()
	TObjectPtr<UWeaponBase> CurrentWeapon = nullptr;
	UPROPERTY(EditAnywhere, Category = "Weapon Setup")
	TSubclassOf<UWeaponBase> DefaultWeaponClass;
};
