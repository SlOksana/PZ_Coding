#include "PistolWeapon.h"

#include "DrawDebugHelpers.h"
#include "FireWeapon.h"
#include "PZ_CodingCharacter.h"
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
	ONInteractFireWeaponMulticast.Broadcast();
	if(!CanStartFire())
	{
		return;
	}
	Reload();
	UseAmmo();
	CanReload();
	CanStartFire();
	ServerFire();
	GetWorld()->GetTimerManager().
	SetTimer(FiringTimer,this,&APistolWeapon::ServerFire,FireRate);
	MulticastInteractWeapon();
}

void APistolWeapon::ServerInteractCurrentWeapon()
{
	FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Muzzle");
	FCollisionQueryParams RV_TraceParams;
	RV_TraceParams.bTraceComplex = true;
	FHitResult RV_Hit(ForceInit);
	FVector LocationEnd = LocationSocket;
	FVector Forward = this->GetActorForwardVector();
	Forward = Forward * Range;
	LocationEnd += Forward;
	GetWorld()->LineTraceSingleByChannel(
	   RV_Hit,
	   LocationSocket,
	   LocationEnd,
	   ECC_Pawn,
	   RV_TraceParams
	);
	DrawDebugLine(
	   GetWorld(),
	   LocationSocket,
	   LocationEnd,
	   FColor(255, 0, 0),
	   false,
	   0.3,
	   0,
	   2
	   );

	if (RV_Hit.bBlockingHit)

	if (RV_Hit.bBlockingHit)

	{
		auto* Character = Cast<APZ_CodingCharacter>(RV_Hit.GetActor());
		if (Character)
		{Character->ApplyDamage();}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *RV_Hit.GetActor()->GetName());
	}


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

