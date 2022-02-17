// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "GameFramework/Actor.h"
#include "FireWeapon.generated.h"

DECLARE_DYNAMIC_DELEGATE(FInteractWeaponDynamic);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractWeaponMulticast);

UCLASS()
class PZ_CODING_API AFireWeapon : public ABaseWeapon, public IInterfaceC
{
	GENERATED_BODY()
	
public:	
	AFireWeapon();
	FTimerHandle WeaponTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Range;
	
	UPROPERTY(BlueprintReadWrite)
	int32 MaxAmmo;
	
	UPROPERTY(BlueprintReadWrite)
	int32 AmmoPerClip;
	
	UPROPERTY(BlueprintReadWrite)
	float ReloadDuration;
	
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmo;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmoClip;

	UPROPERTY(BlueprintReadWrite)
	bool bIsReloading;
	
	UFUNCTION(Server,Unreliable)
	void Reloading();
	
	UFUNCTION(Server,Unreliable)
	void UseAmmo();
	
	UFUNCTION(Server,Unreliable)
	void ServerFire();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanReload();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastInteractWeapon();
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Server,Unreliable)
	virtual void Reload() override;
	UFUNCTION(Server,Unreliable)
	 virtual void ServerInteractCurrentWeapon();
	virtual bool CanStartFire();
	virtual void Tick(float DeltaTime) override;

	FInteractWeaponDynamic OnInteractWeaponDynamic;

	UPROPERTY(BlueprintAssignable)
	FInteractWeaponMulticast ONInteractWeaponMulticast;

};
