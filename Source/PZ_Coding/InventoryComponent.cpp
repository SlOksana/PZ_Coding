
#include "InventoryComponent.h"

#include "NewInventoryItem.h"
#include "Components/BoxComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
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

void UInventoryComponent::AddItem_Implementation(ANewInventoryItem* NewItem, int32 CountItem)
{
NewItem->SetActorHiddenInGame(true);
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

void UInventoryComponent::UseItem_Implementation(ANewInventoryItem* SelectItem)
{
	ANewInventoryItem* NewItem = Cast<ANewInventoryItem>(SelectItem);
		if (NewItem)
	{
		APZ_CodingCharacter* Character = Cast<APZ_CodingCharacter>(GetOwner());
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
			NewItem->InteractItem(Character);
				}
			}
	}

void UInventoryComponent::UseFirstItem_Implementation()
{
	TArray< ANewInventoryItem*> Keys;
	const int32 KeysAmount = MapItem.GetKeys(Keys);
	if (KeysAmount >0)
	{
		UseItem(Keys[0]);
	}
}

void UInventoryComponent::DropItem_Implementation(ANewInventoryItem* SelectItem, int32 CountItem)
{
	auto* NewItem = Cast<ANewInventoryItem>(SelectItem->GetClass());
	auto* CurrentCount = MapItem.Find(SelectItem);
	if(*CurrentCount >= CountItem)
	{
		auto* Owner = Cast<APZ_CodingCharacter>(GetOwner());
		for(int i = 0; i< CountItem; i++)
		{
			const FVector LocationSpawn = Owner->GetActorRightVector() * SelectItem->DistanceDrop;
			const FRotator RotatorSpawn = Owner->GetActorRotation();
			SelectItem->SetActorHiddenInGame(false);
			SelectItem->SetActorLocationAndRotation(LocationSpawn, RotatorSpawn);
			SelectItem->BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		*CurrentCount -= CountItem;
		if (*CurrentCount == 0)
		{
			MapItem.Remove(SelectItem);
		}
	}
	
}

void UInventoryComponent::DropFirstItem_Implementation()
{
	TArray<ANewInventoryItem* > Keys;
	const int32 KeysAmount = MapItem.GetKeys(Keys);
	if (KeysAmount > 0)
	{
		DropItem(Keys[0], *MapItem.Find(Keys[0]));
	}
}

void UInventoryComponent::SetItem(UInventoryItem* Items)
{
	if(Item.Num() < (MaxXItems*MaxYItems))
	{
		Item.AddUnique(Items);
	}
}


void UInventoryComponent::MulticastAddItem_Implementation(UInventoryItem* Items)
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

