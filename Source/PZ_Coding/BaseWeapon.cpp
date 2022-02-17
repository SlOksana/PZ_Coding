

#include "BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "InterfaceC.h"
#include "WeaponInterface.h"
ABaseWeapon::ABaseWeapon()
{	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
void ABaseWeapon::OnOverlap(AActor* OtherActor)
{
	IWeaponInterface * Weapon = Cast<IWeaponInterface>(OtherActor);
	if(Weapon)
	{
		Weapon->SetWeapon(this);
	}
}
void ABaseWeapon::InteractWeapon()
{
	
}
void ABaseWeapon::DropWeapon()
{
	
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

