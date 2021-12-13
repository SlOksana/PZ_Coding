// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "SpyCameraActor.generated.h"

class UBoxComponent;
class UMaterialInterface;
class ABasePawn;
//DECLARE_EVENT(ASpyCameraActor, FOnChangeColor);

UCLASS()
class PZ_CODING_API ASpyCameraActor : public ACameraActor
{
	GENERATED_BODY()
	
public:
	ASpyCameraActor();

	virtual void BeginPlay() override;

	FTimerHandle ChangeColorTimer;

	//FOnChangeColor OnChangeColor;

protected:
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UMaterialInterface* Material;

	ABasePawn* BasePawn;

	//(EditAnywhere)
		//UStaticMeshComponent* MeshComp;

	UFUNCTION()
		void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void ChangeColor();

};
