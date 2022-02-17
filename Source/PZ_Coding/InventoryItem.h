// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PZ_CODING_API UInventoryItem : public UObject
{
	public:
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FName Name;

	UPROPERTY(BlueprintReadWrite)
	UTexture2D* Icon;

	UInventoryItem();
	explicit UInventoryItem(FName Name);
	
};
