// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
TArray<UInventoryItem*>& UInventoryComponent::GetItem()
{
	return Item;
}
UInventoryItem* UInventoryComponent::GetItems(const int32 Number) const 
{
	if (Number>Item.Num())
	{
		return nullptr;
	}
	else
	{
		return Item[Number];
	}
}

bool UInventoryComponent::AddItem(UInventoryItem* Items)
{
	
	Item.Add(Items);
	return true;
}

bool UInventoryComponent::Replete()
{
	return Item.Num()>=Size;
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

