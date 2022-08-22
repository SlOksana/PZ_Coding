// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.h"
#include "Cube_PZ_8.generated.h"

UCLASS()
class PZ_CODING_API ACube_PZ_8 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube_PZ_8();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 AmountOfCubes = rand() % 100 + 1;
	
   	UFUNCTION()
	static FVector Position();
	UFUNCTION()
	static FRotator Rotation();
	
	UFUNCTION()
	void NewCubeCreator();
	UFUNCTION()
	void NewCube(int32 value);
    UFUNCTION()
	void DestroyCube();
	
	TArray<ACube*> CubeArray;
	
	FTimerHandle CubeTimer;
	FTimerHandle DestroyCubeTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
