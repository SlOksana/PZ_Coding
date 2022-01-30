#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceC.h"
#include "BaseWeapon.generated.h"

UCLASS()
class PZ_CODING_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;	
public:	
	ABaseWeapon();

	UStaticMeshComponent* GetStaticMeshComponent() const { return  StaticMeshComponent; }
		
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite)
	int32 Damage;
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* OtherActor);
	virtual void InteractWeapon();
	virtual void Tick(float DeltaTime) override;

};