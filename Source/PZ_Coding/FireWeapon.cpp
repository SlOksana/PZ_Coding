
#include "FireWeapon.h"
#include "DrawDebugHelpers.h"
#include "PZ_CodingCharacter.h"
#include "Kismet/GameplayStatics.h"

AFireWeapon::AFireWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	Range = 1000.0f;
	MaxAmmo = 12;
	AmmoPerClip = 4;
	ReloadDuration = 2.0;
	CurrentAmmo = 12;
	CurrentAmmoClip = 4;
	bIsReloading = false;

}
FString StrInClip = "In Clip ";
FString StrCurrAmmo = "CurAmmo ";
void AFireWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
void AFireWeapon::Reloading_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, ReloadDuration, FColor::Black,
			TEXT("Reloading"));
	if (CurrentAmmo >= AmmoPerClip)
	{
		CurrentAmmoClip += AmmoPerClip - CurrentAmmoClip;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
			StrInClip + FString::FromInt(CurrentAmmoClip));
	} else
	{
		CurrentAmmoClip += CurrentAmmo;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
StrInClip + FString::FromInt(CurrentAmmoClip));
	}
	bIsReloading = false;
}
void AFireWeapon::Reload_Implementation()
{
	if (CanReload())
	{
		bIsReloading = true;
		GetWorldTimerManager().SetTimer(WeaponTimer, this,
			&AFireWeapon::Reloading,  1.0f, false, -1);
	}
}

void AFireWeapon::UseAmmo_Implementation()
{
	--CurrentAmmoClip;
}

void AFireWeapon::ServerFire_Implementation()
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
	{
		auto* Character = Cast<APZ_CodingCharacter>(RV_Hit.GetActor());
		if (Character)
		{}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *RV_Hit.GetActor()->GetName());
	}
}
bool AFireWeapon::CanReload_Implementation()
{
	if (CurrentAmmo > 0 && CurrentAmmoClip < AmmoPerClip)
	{
		return true;
	}
	return false;
}
bool AFireWeapon::CanStartFire()
{
	if (CurrentAmmoClip > 0)
	{
		return true;
	}
	return false;
}

void AFireWeapon::MulticastInteractWeapon_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem,
			GetStaticMeshComponent()->GetSocketTransform(("Muzzle"),
			RTS_World), true, EPSCPoolMethod::AutoRelease,
			true);	
}

void AFireWeapon::ServerInteractCurrentWeapon_Implementation()
{
	ONInteractWeaponMulticast.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("IteractWeapon"));
	FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Muzzle");
	FCollisionQueryParams RV_TraceParams;
	RV_TraceParams.bTraceComplex = true;
	FHitResult RV_Hit(ForceInit);
	FVector LocationEnd = LocationSocket;
	FVector Forward = this->GetActorForwardVector();
	Forward = Forward * Range;
	LocationEnd += Forward;
	MulticastInteractWeapon();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem,
		GetStaticMeshComponent()->GetSocketTransform(("Muzzle"),
		RTS_World), true, EPSCPoolMethod::AutoRelease,
		true);
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
	
	if(!CanStartFire())
	{
		return;
	}
	UseAmmo();
	ServerFire();
}

void AFireWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

