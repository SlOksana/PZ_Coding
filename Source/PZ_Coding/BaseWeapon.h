#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "InterfaceC.h"
#include "BaseWeapon.generated.h"

class USphereComponent;
UCLASS()
class PZ_CODING_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
	public:	
	ABaseWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;
<<<<<<< Updated upstream
=======
	
>>>>>>> Stashed changes

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION(BlueprintCallable)
	 UBoxComponent* GetBoxComponent()  { return  BoxComponent; }

	 UStaticMeshComponent* GetStaticMeshComponent() const { return  StaticMeshComponent; }

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