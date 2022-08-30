// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewInventoryItem.h"
#include "HealthBag.generated.h"

UCLASS()
class PZ_CODING_API AHealthBag : public ANewInventoryItem
{
	GENERATED_BODY()
public:
    AHealthBag();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Health")
	int32 CurrentHealth;

	UFUNCTION(BlueprintCallable)
	virtual void InteractItem(APZ_CodingCharacter* Character ) override;
	
};
