// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireWeapon.h"
#include "GameFramework/Actor.h"
#include "PistolWeapon.generated.h"

UCLASS()
class PZ_CODING_API APistolWeapon : public AFireWeapon
{
	GENERATED_BODY()
	
public:	
	APistolWeapon();
	FTimerHandle FiringTimer;
	
	//UFUNCTION(BlueprintCallable)
   // void Fire();

	UFUNCTION(Server, Reliable)
	void ServerFireFunction();
	
	UPROPERTY(BlueprintReadOnly)
	bool bCanFire;
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate;


protected:
	virtual void BeginPlay() override;

public:
	virtual bool CanStartFire() override;
	virtual void InteractWeapon() override;
	virtual void Tick(float DeltaTime) override;

};
