// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZ_CodingCharacter.h"
#include "GameFramework/Actor.h"
#include "NewInventoryItem.generated.h"

UCLASS()
class PZ_CODING_API ANewInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ANewInventoryItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess = " true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess = " true"))
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceDrop;
	
protected:
	virtual void BeginPlay() override;

public:
	
	virtual void InteractItem(APZ_CodingCharacter* Character );
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void Tick(float DeltaTime) override;

};
