#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InventoryInterface.h"
#include "WeaponInterface.h"
#include "PZ_CodingCharacter.generated.h"

UCLASS(config=Game)
class APZ_CodingCharacter : public ACharacter, public IInventoryInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
    	class UWeaponManagerComponent* WeaponManagerComp;

	
public:
	APZ_CodingCharacter();
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USceneComponent* SceneComp;
	
	UPROPERTY(Category="Character", VisibleAnywhere,BlueprintReadWrite, meta=(AllowPublicAccess = "true"))
	UInventoryComponent* InventoryComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AnimMontageClimb;
	
    UFUNCTION(BlueprintCallable, BlueprintPure)
    	bool CheckIsAndroid();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool IsClimbing;
	
	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;}

	   // UFUNCTION(BlueprintCallable)
	//void ForwardHeightTrace();
	
  //  UFUNCTION(Server, Unreliable)
	//void ServerForwardHeightTrace();

	void DropItem();
	void UseItem();
	
	UFUNCTION(BlueprintCallable)
	void ApplyDamage( );

	UFUNCTION(Client, Unreliable)
	void AddHealthClient(float NewValue);

	UFUNCTION(Server, Unreliable)
	void AddHealthServer(float NewValue);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastClimbAnim();

	void OnSetWeapon(ABaseWeapon* NewWeapon = nullptr);
	
	UFUNCTION(BlueprintCallable)
	virtual UInventoryComponent* GetInventory() override;
	virtual void Inventory() override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	void OnDropWeapon();
	void OnResetVR();
	UFUNCTION(NetMulticast, Reliable)
	void RespawnCharacter();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

