
#include "NewInventoryItem.h"

#include "Components/BoxComponent.h"

ANewInventoryItem::ANewInventoryItem()
{
	PrimaryActorTick.bCanEverTick = true;
	DistanceDrop = 50.0f;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMrsh"));
	StaticMesh->SetupAttachment(GetRootComponent());
}

void ANewInventoryItem::BeginPlay()
{
	Super::BeginPlay();
	this->SetReplicates(true);
	this->SetReplicateMovement(true);
	
	
}

void ANewInventoryItem::InteractItem(APZ_CodingCharacter* Character)
{
}

void ANewInventoryItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	auto* Character = Cast<APZ_CodingCharacter>(OtherActor);
	if(IsValid(Character))
	{
		Character->GetItem(this);
		this->SetActorHiddenInGame(true);
		this->BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
}

void ANewInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

