#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "NewInventoryItem.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PZ_CODING_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	 UPROPERTY(EditAnywhere)
	TArray<class UInventoryItem*> Item;

	UPROPERTY()
	TMap<class ANewInventoryItem*, int32> MapItem;

	UPROPERTY(BlueprintReadWrite)
	int32 Size = 15;
	
	UPROPERTY(BlueprintReadWrite,Category="Items",EditAnywhere)
	int32 MaxXItems;
	UPROPERTY(BlueprintReadWrite,Category="Items",EditAnywhere)
	int32 MaxYItems;
	
	UFUNCTION(BlueprintCallable)
	TArray<UInventoryItem*>& GetItem();

	void DropItem_Implementation(ANewInventoryItem* SelectItem, int32 CountItem);
	UFUNCTION(BlueprintCallable)
	void SetItem(UInventoryItem* Items);
	

	UFUNCTION(BlueprintCallable)
	UInventoryItem* GetItems(const int32 Number) const;

	UFUNCTION(Server,BlueprintCallable, Unreliable)
	void AddItem(ANewInventoryItem* NewItem, int32 CountItem);

	UFUNCTION(Server,BlueprintCallable, Unreliable)
	void UseItem(ANewInventoryItem* SelectItem);

	UFUNCTION(Server,BlueprintCallable, Unreliable)
	void UseFirstItem();

	UFUNCTION(Server,BlueprintCallable, Unreliable)
	void DropItem(ANewInventoryItem* SelectItem, int32 CountItem);

	UFUNCTION(Server,BlueprintCallable, Unreliable)
	void DropFirstItem();
	
	UFUNCTION(BlueprintCallable)
	bool Replete();
	
	UFUNCTION(NetMulticast,BlueprintCallable,Reliable)
	void MulticastAddItem(UInventoryItem* Items);

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
