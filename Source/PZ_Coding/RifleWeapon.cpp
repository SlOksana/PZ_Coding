// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleWeapon.h"
#include "PZ_CodingCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

ARifleWeapon::ARifleWeapon()
{
	MaxAmmo = 12;
	CurrentAmmoClip = 4;
	AmmoPerClip = 4;
	Duration = 100.0f;
}
void ARifleWeapon::InteractWeapon()
{
	ONInteractWeaponMulticast.Broadcast();
	if(!CanStartFire())
	{
		return;
	}
	UseAmmo();
	ServerFire();
	GetWorld()->GetTimerManager().
	SetTimer(FiringTimer,this,&ARifleWeapon::ServerFire,FireRate);
	MulticastInteractWeapon();
}
void ARifleWeapon::ServerInteractCurrentWeapon_Implementation()
{
	ONInteractWeaponMulticast.Broadcast();
	FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Muzzle");
	FCollisionQueryParams RV_TraceParams;
	RV_TraceParams.bTraceComplex = true;
	FHitResult RV_Hit(ForceInit);
	FVector LocationEnd = LocationSocket;
	FVector Forward = this->GetActorForwardVector();
	Forward = Forward * Range;
	Forward.Z += UKismetMathLibrary::RandomIntegerInRange(-100,100);
	Forward.Y += UKismetMathLibrary::RandomIntegerInRange(-100,100);
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
	{
		auto* Character = Cast<APZ_CodingCharacter>(RV_Hit.GetActor());
		if (Character)
		{}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *RV_Hit.GetActor()->GetName());
	}
	
	if(!CanStartFire())
	{
		return;
	}
	UseAmmo();
	ServerFire();
}
