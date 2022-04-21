#pragma once

#include "CoreMinimal.h"
#include "FireWeapon.h"
#include "ThrowingWeapon.h"
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ProjectilesAmount;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay|Projectile")
	TSubclassOf<class AThrowingWeapon> Grenade;
	
	virtual void ServerInteractCurrentWeapon_Implementation() override;
	void Tick(float DeltaTime);
	virtual void InteractWeapon() override;

};
