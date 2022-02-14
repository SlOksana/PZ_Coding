#include "InventoryItem.h"
#include "Components/BoxComponent.h"


AInventoryItem::AInventoryItem()
{
	PrimaryActorTick.bCanEverTick = true;
	DistanceDrop = 300.0f;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMrsh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	
}

void AInventoryItem::InteractItem(APZ_CodingCharacter* Character)
{
}

AInventoryItem::AInventoryItem(FName Name)
{
	this->Name = Name;
}

