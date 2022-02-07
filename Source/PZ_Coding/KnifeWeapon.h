// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "FireWeapon.h"
#include "KnifeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PZ_CODING_API AKnifeWeapon :  public AFireWeapon
{
	GENERATED_BODY()
//	AKnifeWeapon::AKnifeWeapon();
	
public:
	virtual void InteractWeapon() override;
	virtual void ServerInteractCurrentWeapon_Implementation() override;
	
};
