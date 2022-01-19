// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PZ_CODING_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	 UPROPERTY(EditAnywhere)
	TArray<UInventoryItem*> Item;

	UPROPERTY(BlueprintReadWrite)
	int32 Size = 15;

	UFUNCTION(BlueprintCallable)
	TArray<UInventoryItem*>& GetItem();

	UFUNCTION(BlueprintCallable)
	UInventoryItem* GetItems(const int32 Number) const;

	UFUNCTION(BlueprintCallable)
	bool AddItem(UInventoryItem* Items);

	UFUNCTION(BlueprintCallable)
	bool Replete();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
