// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceC.h"
#include "Weapon.generated.h"

UCLASS()
class PZ_CODING_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USceneComponent* SceneComp;

   UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName MuzzleSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Range;
	
	UPROPERTY(BlueprintReadWrite)
	int32 MaxAmmo;
	
	UPROPERTY(BlueprintReadWrite)
	int32 AmmoPerClip;

	UPROPERTY(BlueprintReadWrite)
	int32 Damage;

     UPROPERTY(BlueprintReadWrite)
	float ReloadDuration;
	
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmo;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmoClip;

	UPROPERTY(BlueprintReadWrite)
	bool bIsReloading;
	
	UFUNCTION(BlueprintCallable)
	void WeaponTrace();
     
    UFUNCTION(BlueprintCallable)
    void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();
	
	UFUNCTION(BlueprintCallable)
	bool CanFire();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Reload();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanReload();

	UFUNCTION(BlueprintCallable)
	void Reloading();

	UFUNCTION()
	void UseAmmo();
	
	FTimerHandle WeaponTimer;
    UPROPERTY(EditDefaultsOnly, Category="Gameplay|Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	//UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	//float FireRate;

    // FTimerHandle FiringTimer;
		
protected:
	virtual void BeginPlay() override;

public:	
   // virtual void IteractWeapon();
	virtual void Tick(float DeltaTime) override;

};
