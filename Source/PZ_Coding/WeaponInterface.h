// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BaseWeapon.h"
#include "WeaponInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class PZ_CODING_API IWeaponInterface
{
	GENERATED_BODY()

public:
	virtual void SetWeapon(ABaseWeapon * BaseWeapon) = 0;
};
