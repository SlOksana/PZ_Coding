// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Cube.generated.h"

UENUM(BlueprintType)
enum class Status:uint8
{
	Moving = 0 UMETA(DisplayName = "Moving"),
	Stopped = 1 UMETA(DisplayName = "Stopped"),
	MAX
};
UCLASS()
class PZ_CODING_API ACube : public AActor
{
	GENERATED_BODY()
	
public:	
	ACube();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Cube;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<Status> status;

	UFUNCTION()
	void Status();

	FTimerHandle StatusTimer;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
