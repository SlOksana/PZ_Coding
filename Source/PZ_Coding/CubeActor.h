// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeActor.generated.h"

UCLASS()
class PZ_CODING_API ACubeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeActor();

	UPROPERTY(BlueprintReadWrite)
		int32 Life;

	UFUNCTION(BlueprintCallable)
		void SetLife(int32 CurrentLife);

	UFUNCTION(BlueprintCallable)
		int32 GetLife();

	FTimerHandle DestroyCude;

	void DestroyCudeFunction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
