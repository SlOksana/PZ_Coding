// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacterC.generated.h"
DECLARE_EVENT(AMainCharacterC, FDestroyActor);
DECLARE_EVENT(AMainCharacherC, FDamageActor);
UCLASS()
class PZ_CODING_API AMainCharacterC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacterC();

	UPROPERTY(BlueprintReadWrite)
		int32 Health;

	UPROPERTY(BlueprintReadWrite)
		int32 Stamina;
  

	UFUNCTION(BlueprintCallable)
	void SetHealth(int32 CurrentHealth);

	UFUNCTION(BlueprintCallable)
		int32 GetHealth();


	UFUNCTION(BlueprintCallable)
		int32 GetRestorationHealth();


	UFUNCTION(BlueprintCallable)
		void DestroyA();

	UFUNCTION(BlueprintCallable)
		void DamageA();

	FDestroyActor DestroyActor;
	FDamageActor DamageActor;

	FTimerHandle TimerDamage;
	FTimerHandle TimerHealth;

	void RepeatingFunctionDamage();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
