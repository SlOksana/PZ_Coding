// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Weapon.h"
#include "BaseWeapon.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PZ_CODING_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponManagerComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABaseWeapon* CurrentWeapon;
	int32 DistanceToDropWeapon;
		
	UFUNCTION(BlueprintCallable)
	  bool SetCurrentWeapon(ABaseWeapon* NewWeapon);
	
	UFUNCTION(BlueprintCallable)
	void ReloadCurrentWeapon();
	
	UFUNCTION(Server, Unreliable)
	void InteractCurrentWeapon();

	UFUNCTION(Server,BlueprintCallable, Unreliable)
	void DropCurrentWeapon();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
