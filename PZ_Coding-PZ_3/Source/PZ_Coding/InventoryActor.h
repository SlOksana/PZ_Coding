#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InventoryActor.generated.h"

UCLASS()
class PZ_CODING_API AInventoryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComponent;


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComponent;

	UFUNCTION()
	void OnComponentBeginOvelrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBofyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
};
