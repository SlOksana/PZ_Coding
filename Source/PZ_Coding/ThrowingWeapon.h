#pragma once
#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "FireWeapon.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ThrowingWeapon.generated.h"

DECLARE_DYNAMIC_DELEGATE(FInteractThrowingWeaponDynamic);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractThrowingWeaponMulticast);

UCLASS()
class PZ_CODING_API  AThrowingWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	AThrowingWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Gameplay|Projectile")
	TSubclassOf<class AThrowingWeapon> ProjectileClass;
	
	virtual void InteractWeapon();
	
	UFUNCTION(BlueprintCallable)
	USphereComponent* GetSphereComponent()  { return  SphereComponent; }


	UFUNCTION(Client, Unreliable)
	void InteractWeaponClient();

	UFUNCTION(Server, Unreliable)
	void InteractWeaponServer();

	UFUNCTION(NetMulticast, Unreliable)
	 void InteractWeaponMulticast();

	FTimerHandle TimerToBoom;
	void OnTimerToBoom();
	
	void DestroyGrenade();
	float TimeToDestroy;
	
protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	FInteractThrowingWeaponDynamic OnInteractThrowingWeaponDynamic;

	UPROPERTY(BlueprintAssignable)
	FInteractThrowingWeaponMulticast OnInteractThrowingWeaponMulticast;
};

	
	
	
