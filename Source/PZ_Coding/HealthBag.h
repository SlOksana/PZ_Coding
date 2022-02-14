// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "HealthBag.generated.h"

UCLASS()
class PZ_CODING_API AHealthBag : public AInventoryItem
{
	GENERATED_BODY()
public:
    AHealthBag();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Health")
	int32 Health;

	UFUNCTION(BlueprintCallable)
	virtual void InteractItem(APZ_CodingCharacter* Character ) override;
	
};
