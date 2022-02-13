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
TArray<AInventoryItem*>& UInventoryComponent::GetItem()
{
	return Item;
}
AInventoryItem* UInventoryComponent::GetItems(const int32 Number) const 
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

void UInventoryComponent::AddItem(TSubclassOf<AInventoryItem> NewItem, int32 CountItem)
{
	auto* CurrentCount = MapItem.Find(NewItem);
	if(MapItem.Find(NewItem) == nullptr)
	{
		MapItem.Add(NewItem, CountItem);
	}
	else
	{
		CurrentCount += CountItem;
	}
}

bool UInventoryComponent::UseItem(TSubclassOf<AInventoryItem> SelectItem)
{
	auto* Item = Cast<AInventoryItem>(SelectItem.Get());
	if (Item)
	{
		auto* Character = Cast<APZ_CodingCharacter>(GetOwner());
		auto* CurrentCount = MapItem.Find(SelectItem);
		if(Character)
		{
			if(*CurrentCount == 1)
			{
				MapItem.Remove(SelectItem);
			}
			else
			{
				CurrentCount -= 1;
			}
			Item->InteractItem(Character);
			return true;
		}
			}
	return false;
}

void UInventoryComponent::UseFirstItem()
{
	TArray<TSubclassOf<AInventoryItem>> Keys;
	MapItem.GetKeys(Keys);
	UseItem(Keys[0]);
}

void UInventoryComponent::DropItem(TSubclassOf<AInventoryItem> SelectItem, int32 CountItem)
{
	auto* Item = Cast<AInventoryItem>(SelectItem->GetClass());
	auto* CurrentCount = MapItem.Find(SelectItem);
	if(*CurrentCount >= CountItem)
	{
		auto* Owner = GetOwner();
		for(int i = 0; i< CountItem; i++)
		{
			const FVector LocationSpawn = Owner->GetActorLocation()+300;
			//const FRotator RotatorSpawn = Owner->GetActorRotation();
			FHitResult* OutSweepHitResult = nullptr;
			Owner->SetActorLocation(LocationSpawn,false,OutSweepHitResult,ETeleportType::None);
		}
		CurrentCount -= CountItem;
		if (CurrentCount == 0)
		{
			MapItem.Remove(SelectItem);
		}
	}
	
}

void UInventoryComponent::DropFirstItem()
{
	TArray<TSubclassOf<AInventoryItem>> Keys;
	MapItem.GetKeys(Keys);
	DropItem(Keys[0], *MapItem.Find(Keys[0]));
}

void UInventoryComponent::SetItem(AInventoryItem* Items)
{
	if(Item.Num() < (MaxXItems*MaxYItems))
	{
		Item.AddUnique(Items);
	}
}


void UInventoryComponent::MulticastAddItem_Implementation(AInventoryItem* Items)
{
	Item.Add(Items);
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

