#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceC.h"
#include "BaseWeapon.generated.h"

class UBoxComponent;
UCLASS()
class PZ_CODING_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	 UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

public:	
	ABaseWeapon();

	UStaticMeshComponent* GetStaticMeshComponent() const { return  StaticMeshComponent; }
	UBoxComponent* GetBoxComponent() const { return  BoxComponent; }
		
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ParticleSystem;
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* OtherActor);
	
	UFUNCTION(BlueprintCallable)
	virtual void DropWeapon();


	virtual void InteractWeapon();
	virtual void Tick(float DeltaTime) override;

};