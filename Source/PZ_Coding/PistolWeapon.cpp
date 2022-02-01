#include "PistolWeapon.h"
#include "FireWeapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APistolWeapon::APistolWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanFire = true;
	FireRate = 0.25f;
}

void APistolWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
void APistolWeapon::InteractWeapon()
{
	ONInteractWeaponMulticast.Broadcast();
	if(!CanStartFire())
	{
		return;
	}
	UseAmmo();
	ServerFire();
	GetWorld()->GetTimerManager().
	SetTimer(FiringTimer,this,&APistolWeapon::ServerFire,FireRate);
	MulticastInteractWeapon();
}
void APistolWeapon::ServerFireFunction_Implementation()
{
	bCanFire = true;
}

bool APistolWeapon::CanStartFire()
{
	return Super::CanStartFire() && bCanFire;
}

void APistolWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
