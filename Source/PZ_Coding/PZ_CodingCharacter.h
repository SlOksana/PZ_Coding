// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "PZ_CodingCharacter.generated.h"

UCLASS(config=Game)
class APZ_CodingCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	APZ_CodingCharacter();
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName MuzzleSocketName;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Weapon")
	AWeapon* CurrentWeapon = nullptr;

		
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponAttachSocketName = "WeaponSocket";
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;}

	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetCurrentHealth() const {return CurrentHealth;}

	UFUNCTION(BlueprintCallable, Category="Health")
	void SetCurrentHealth(float healthValue);

	UFUNCTION(BlueprintCallable, Category="Health")
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser ) override;

protected:
	virtual void BeginPlay() override;


	
	UPROPERTY()
	class UChildActorComponent* WeaponComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth)
	float CurrentHealth;
	

//	UPROPERTY(EditDefaultsOnly, Category="Gameplay|Projectile")
//	TSubclassOf<class AProjectile> ProjectileClass;

//	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
//	float FireRate;

bool bIsFiringWeapon;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void StartFire();

//	UFUNCTION(BlueprintCallable, Category = "Gameplay")
//	void StopFire();
	
	//UFUNCTION(Server, Reliable)
	//void HandleFire();

	//FTimerHandle FiringTimer;


	UFUNCTION()
	void OnRep_CurrentHealth();

	void OnHealth_Update();
	
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

