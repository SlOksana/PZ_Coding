#include "RifleWeapon.h"
#include "PZ_CodingCharacter.h"
#include "DrawDebugHelpers.h"
#include "ThrowingWeapon.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ARifleWeapon::ARifleWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	MaxAmmo = 16;
	CurrentAmmoClip = 12;
	AmmoPerClip = 12;
	CurrentAmmo = 16;
	Duration = 1000.0f;
	Lines = 3;
	FireRate =0.25f;
	bIsReloading = false;
	//Projectile = AProjectile::StaticClass();
}
void ARifleWeapon::InteractWeapon()
{
	ONInteractFireWeaponMulticast.Broadcast();
	if(!CanStartFire())
	{
		return;
	}
	Reload();
	UseAmmo();
	CanReload();
	//CanStartFire();
	GetWorld()->GetTimerManager().
	SetTimer(FiringTimer,this,&ARifleWeapon::ServerFire,FireRate);
    MulticastInteractWeapon();
	
}

void ARifleWeapon::ServerInteractCurrentWeapon_Implementation()
{   FVector spawnLocation = GetStaticMeshComponent()->GetSocketLocation("Grenade");
	FRotator Rotation = this->GetActorRotation();
	Rotation.Pitch += UKismetMathLibrary::RandomFloatInRange(-10.f,10.f);
	//Rotation.Yaw += UKismetMathLibrary::RandomFloatInRange(-10.f,10.f);
	FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Muzzle");
	FVector Forward = this->GetActorForwardVector();
	FVector LocationEnd = LocationSocket;
	for (int32 i=0; i<Lines; i++)
	{
		Rotation.Yaw += UKismetMathLibrary::RandomFloatInRange(-10.f,10.f);
		FCollisionQueryParams RV_TraceParams;
		RV_TraceParams.bTraceComplex = true;
		FHitResult RV_Hit(ForceInit);
		FVector NewForward = Forward * Range;
		NewForward.Z += UKismetMathLibrary::RandomIntegerInRange(-200,200);
		NewForward.Y += UKismetMathLibrary::RandomIntegerInRange(-200,200);
		LocationEnd += NewForward;
		GetWorld()->SpawnActor(Grenade,&spawnLocation,&Rotation);
   
		GetWorld()->LineTraceSingleByChannel(
		   RV_Hit,
		   LocationSocket,
		   LocationEnd,
		   ECC_Pawn,
		   RV_TraceParams
		);
		if (RV_Hit.bBlockingHit)
		{
			auto* Character = Cast<APZ_CodingCharacter>(RV_Hit.GetActor());
			if (Character)
			{Character->ApplyDamage();}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *RV_Hit.GetActor()->GetName());
		}
 	}
			
}

void ARifleWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


