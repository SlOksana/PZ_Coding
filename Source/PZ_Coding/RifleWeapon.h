#pragma once

#include "CoreMinimal.h"
#include "FireWeapon.h"
#include "ThrowingWeapon.h"
#include "Projectile.h"
#include "RifleWeapon.generated.h"

UCLASS()
class PZ_CODING_API ARifleWeapon : public AFireWeapon
{
	GENERATED_BODY()
	ARifleWeapon();

public:
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate;
	UPROPERTY(EditAnywhere)
	float Duration;
	int32 Lines;
	FTimerHandle TimerToBoom;
	FTimerHandle FiringTimer;
	UPROPERTY(EditDefaultsOnly, Category="Gameplay|Projectile")
	TSubclassOf<class AThrowingWeapon> Grenade;
	virtual void ServerInteractCurrentWeapon_Implementation() override;
	virtual void InteractWeapon() override;

};
