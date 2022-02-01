// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireWeapon.h"
#include "RifleWeapon.generated.h"

UCLASS()
class PZ_CODING_API ARifleWeapon : public AFireWeapon
{
	GENERATED_BODY()
	ARifleWeapon();

public:
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate =0.25f;
	UPROPERTY(EditAnywhere)
	float Duration = 100.0f;
	FTimerHandle FiringTimer;
	virtual void ServerInteractCurrentWeapon_Implementation() override;
	//virtual bool CanStartFire() override;
	virtual void InteractWeapon() override;
};
