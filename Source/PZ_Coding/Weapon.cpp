// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "InterfaceC.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
//#include "Components/SlateWrapperTypes.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	SceneComp = CreateDefaultSubobject<USceneComponent>("Scene");

	SetRootComponent(SceneComp);
	WeaponMesh->SetupAttachment(RootComponent);

	MuzzleSocketName = "Muzzle";
    Range = 1000.0f;
	MaxAmmo = 12;
	AmmoPerClip = 4;
	Damage = 6;
	ReloadDuration = 2.0;
	CurrentAmmo = 12;
	CurrentAmmoClip = 4;
	bIsReloading = false;
	ProjectileClass = AProjectile::StaticClass();
	FireRate = 0.25f;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}


void AWeapon::WeaponTrace()
{
    FVector Location;
	FRotator Rotation;
	FVector StartTrace = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	FVector  EndTrace = GetActorForwardVector()  * Range +StartTrace;
	DrawDebugLine(GetWorld(),StartTrace,EndTrace,FColor::Red,false,1.0f,0,0.5f );
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility);
	if (HitResult.bBlockingHit)
	{
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint,
			FVector(10, 10, 10), FColor::Magenta, false, 2.0f);
	}
}

bool AWeapon::CanFire()
{
	if (CurrentAmmoClip > 0)
	{
		return true;
	}
	return false;
}

FString InClip = "In Clip ";
FString CurrAmmo = "CurAmmo ";

void AWeapon::UseAmmo()
{
	--CurrentAmmoClip;
}

void AWeapon::Fire()
{
	if (CanFire())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue,
			CurrAmmo + FString::FromInt(CurrentAmmo));
		WeaponTrace();
		HandleFire();
		--CurrentAmmo;
		UseAmmo();
		if(CurrentAmmoClip == 0)
		{
			Reload_Implementation();
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
			InClip + FString::FromInt(CurrentAmmoClip));
}

bool AWeapon::CanReload_Implementation()
{
	if (CurrentAmmo > 0 && CurrentAmmoClip < AmmoPerClip)
	{
		return true;
	}
	return false;
}

void AWeapon::Reload_Implementation()
{
	if (CanReload())
	{
		bIsReloading = true;
		GetWorldTimerManager().SetTimer(WeaponTimer, this,
			&AWeapon::Reloading,  1.0f, false, -1);
	}
}

void AWeapon::Reloading()
{
	GEngine->AddOnScreenDebugMessage(-1, ReloadDuration, FColor::Black,
			TEXT("Reloading"));
	if (CurrentAmmo >= AmmoPerClip)
	{
		CurrentAmmoClip += AmmoPerClip - CurrentAmmoClip;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
			InClip + FString::FromInt(CurrentAmmoClip));
	} else
	{
		CurrentAmmoClip += CurrentAmmo;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
InClip + FString::FromInt(CurrentAmmoClip));
	}
	bIsReloading = false;
}

void AWeapon::HandleFire_Implementation()
{
	FVector SocketLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	FRotator SocketRotation= GetActorRotation();
	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;
	AProjectile* spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(SocketLocation, SocketRotation, spawnParameters);

	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

