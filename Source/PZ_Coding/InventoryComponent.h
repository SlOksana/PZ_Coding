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
	TArray<AInventoryItem*> Item;

	UPROPERTY(BlueprintReadWrite)
	int32 Size = 15;
	
	UPROPERTY(BlueprintReadWrite,Category="Items",EditAnywhere)
	int32 MaxXItems;
	UPROPERTY(BlueprintReadWrite,Category="Items",EditAnywhere)
	int32 MaxYItems;
	
	UFUNCTION(BlueprintCallable)
	TArray<AInventoryItem*>& GetItem();
	
	UFUNCTION(BlueprintCallable)
	void SetItem(AInventoryItem* Items);
	

	UFUNCTION(BlueprintCallable)
	AInventoryItem* GetItems(const int32 Number) const;

	UFUNCTION(BlueprintCallable)
	void AddItem(TSubclassOf<AInventoryItem> NewItem, int32 CountItem);

	UFUNCTION(BlueprintCallable)
	bool UseItem(TSubclassOf<AInventoryItem> SelectItem);

	UFUNCTION(BlueprintCallable)
	void UseFirstItem();

	UFUNCTION(BlueprintCallable)
	void DropItem(TSubclassOf<AInventoryItem> SelectItem, int32 CountItem);

	UFUNCTION(BlueprintCallable)
	void DropFirstItem();
	
//	UFUNCTION(BlueprintCallable)
//	bool AddItem(UInventoryItem* Items);

	UFUNCTION(BlueprintCallable)
	bool Replete();
	
	/*UFUNCTION(Client, Reliable)
    	void ClientAddItem(UInventoryItem* Items);
UFUNCTION(Server, BlueprintCallable, Reliable)
	void ServerAddItem(UInventoryItem* Items);*/
	UFUNCTION(NetMulticast,BlueprintCallable,Reliable)
	void MulticastAddItem(AInventoryItem* Items);

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TMap<TSubclassOf<AInventoryItem>, int32> MapItem;
};
