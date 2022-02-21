
#include "ThrowingWeapon.h"
#include "PZ_CodingCharacter.h"
#include "RifleWeapon.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AThrowingWeapon::AThrowingWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->InitSphereRadius(37.5f);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));
  	RootComponent = SphereComponent;
	StaticMeshComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(GetSphereComponent());
	ProjectileMovementComponent->InitialSpeed = 900.0f;
	ProjectileMovementComponent->MaxSpeed = 2000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.2f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	TimeToDestroy = 0,5.f;
}

void AThrowingWeapon::InteractWeapon()
{
	

	FHitResult RV_Hit(ForceInit); 
	if(GetOwner()) 
	{ 
		auto* Character = Cast<APZ_CodingCharacter>(GetOwner()); 
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform); 
		Character->OnSetWeapon(); 
		SetOwner(nullptr); 
		ProjectileMovementComponent->SetVelocityInLocalSpace(FVector(400,0,0)); 
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f; 
	} 
	else 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("AThrowingWeapon::InteractWeapon Owner is nullptr")); 
	}

	}



void AThrowingWeapon::OnTimerToBoom()
{
	
	OnInteractThrowingWeaponMulticast.Broadcast();
	
UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ParticleSystem,
			GetStaticMeshComponent()->GetSocketTransform("Grenade", RTS_World),
			true,
			EPSCPoolMethod::AutoRelease,
			true
		);

	

}
void AThrowingWeapon::DestroyGrenade()
{
	GetWorld()->GetTimerManager().SetTimer(TimerToBoom,this,&AThrowingWeapon::InteractWeaponMulticast,TimeToDestroy);
}
void AThrowingWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if(HasAuthority())
	{
		DestroyGrenade();
	}

	
	}

void AThrowingWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if(HasAuthority() && !Cast<AThrowingWeapon>(OtherActor))
	{
		InteractWeaponMulticast();
	}
}

void AThrowingWeapon::InteractWeaponMulticast_Implementation()
{
	
	if(GetWorld()->GetTimerManager().IsTimerActive(TimerToBoom))
	{
		Destroy();
			GetWorld()->GetTimerManager().ClearTimer(TimerToBoom);
	}

}

void AThrowingWeapon::InteractWeaponServer_Implementation()
{
	OnInteractThrowingWeaponMulticast.Broadcast();

	InteractWeaponMulticast();
	
//	Destroy();
}

void AThrowingWeapon::InteractWeaponClient_Implementation()
{}
