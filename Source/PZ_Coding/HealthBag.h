// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "HealthBag.generated.h"

UCLASS()
class PZ_CODING_API AHealthBag : public AInventoryItem
{
	GENERATED_BODY()

	AHealthBag::AHealthBag();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Health")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	int32 CurrentHealth;

	UFUNCTION(BlueprintCallable)
	void AddHealth(int32 Value);
	
	UFUNCTION(BlueprintCallable)
	virtual void InteractItem(APZ_CodingCharacter* Character ) override;
	
};
