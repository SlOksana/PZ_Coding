#pragma once
#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "InterfaceC.h"
#include "FireWeapon.generated.h"
DECLARE_DYNAMIC_DELEGATE(FInteractFireWeaponDynamic);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractFireWeaponMulticast);

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ReloadDuration;
	
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmo;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmoClip;

	UPROPERTY(BlueprintReadWrite)
	bool bIsReloading;
	
	UFUNCTION(NetMulticast,Unreliable)
	void Reloading();
	
	UFUNCTION(NetMulticast,Unreliable)
	void UseAmmo();
	
	UFUNCTION(NetMulticast,Unreliable)
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
	
	
	UFUNCTION(NetMulticast,Unreliable)
	virtual void ServerInteractCurrentWeapon();
		
	virtual bool CanStartFire();
	virtual void Tick(float DeltaTime) override;

	FInteractFireWeaponDynamic OnInteractFireWeaponDynamic;

	UPROPERTY(BlueprintAssignable)
	FInteractFireWeaponMulticast ONInteractFireWeaponMulticast;

};
