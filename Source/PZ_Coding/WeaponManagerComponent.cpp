#include "WeaponManagerComponent.h"
#include "InterfaceC.h"
#include "PZ_CodingCharacter.h"
#include "ShooterCharacter.h"
#include "Components/BoxComponent.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DistanceToDropWeapon = 100.0f;
	
}


void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void UWeaponManagerComponent::SetCurrentWeapon(ABaseWeapon* NewWeapon)
{

	
	if (!CurrentWeapon)
	{
		CurrentWeapon = NewWeapon;
		auto* Character = Cast<APZ_CodingCharacter>(GetOwner());
		
		CurrentWeapon->SetOwner(GetOwner());
		CurrentWeapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
									FName(TEXT("SocketWeapon")));
		CurrentWeapon->SetActorRelativeLocation(FVector(-100,0,20));
		CurrentWeapon->SetActorRelativeRotation(FRotator(-40,200,-190));
		CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}


}

void UWeaponManagerComponent::SetShooterCurrentWeapon(ABaseWeapon* NewWeapon)
{
	if (!CurrentWeapon)
	{
		CurrentWeapon = NewWeapon;
		auto* Character = Cast<AShooterCharacter>(GetOwner());
		
		CurrentWeapon->SetOwner(GetOwner());
		CurrentWeapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
									FName(TEXT("SocketWeapon")));
		CurrentWeapon->SetActorRelativeLocation(FVector(40,50,100));
		CurrentWeapon->SetActorRelativeRotation(FRotator(180,290,180));
		CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void UWeaponManagerComponent::ReloadCurrentWeapon()
{
	if(CurrentWeapon)
	{
		IInterfaceC *  ReloadWeapon = Cast<IInterfaceC>(CurrentWeapon);
		if(ReloadWeapon)
		{
			ReloadWeapon->Reload();
		}
	}
}



void UWeaponManagerComponent::InteractCurrentWeapon_Implementation()
{
	
	if (CurrentWeapon)
	{
		CurrentWeapon->InteractWeapon();
	}

}

void UWeaponManagerComponent::DropCurrentWeapon_Implementation()
{
	if(CurrentWeapon)
	{
		CurrentWeapon->SetOwner(nullptr);
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		auto* Character = Cast<APZ_CodingCharacter>(GetOwner());
		 FVector NewLocation = Character->GetMesh()->GetRightVector() * DistanceToDropWeapon + Character->GetMesh()->GetComponentLocation();
		NewLocation.Z += 80;
		FHitResult* OutSweepHitResult = nullptr;
		CurrentWeapon->SetActorLocation(NewLocation,false,OutSweepHitResult,ETeleportType::None);
		CurrentWeapon->DropWeapon();
		CurrentWeapon = nullptr;
	}
	
}

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

