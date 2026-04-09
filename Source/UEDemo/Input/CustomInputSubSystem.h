#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FPlayerInputConfig.h"
#include "CustomInputSubSystem.generated.h"

UCLASS()
class UEDEMO_API UCustomInputSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	FPlayerInputConfig InputConfig;

private:
	void InitInputActions();
	void InitMappingContext();
};