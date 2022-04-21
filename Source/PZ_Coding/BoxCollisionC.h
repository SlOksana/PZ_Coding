#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxCollisionC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitMulticast);
DECLARE_DYNAMIC_DELEGATE(FOnHitDynamic);
UCLASS()
class PZ_CODING_API ABoxCollisionC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxCollisionC();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BoxCollisionComponent;

	UPROPERTY(BlueprintAssignable)
		FOnHitMulticast OnHitMulticast;
          
	    FOnHitDynamic OnHitDynamic;

		UFUNCTION(BlueprintCallable)
			void NewLocation();

		UFUNCTION(BlueprintImplementableEvent)
			void MulticastEvent();

		UFUNCTION(BlueprintCallable)
			void PrimitiveComponent (UPrimitiveComponent* HitComponent, 
				AActor* OtherActor, UPrimitiveComponent* OtherComp, 
				FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
