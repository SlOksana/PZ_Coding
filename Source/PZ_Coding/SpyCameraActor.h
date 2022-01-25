// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "SpyCameraActor.generated.h"

class UBoxComponent;
class UMaterialInterface;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class ABasePawn;

UCLASS()
class PZ_CODING_API ASpyCameraActor : public ACameraActor
{
	GENERATED_BODY()
	
public:
	ASpyCameraActor();

	virtual void BeginPlay() override;

	FTimerHandle ChangeColorTimer;
	FTimerHandle OldColorTimer;
	UStaticMeshComponent* Mesh;
	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicMaterial;

	ABasePawn* BasePawn;

protected:
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BoxComp;
	
	UFUNCTION()
		void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void ChangeColor();


};
