#include "WeaponManagerComponent.h"
#include "InterfaceC.h"
#include "PZ_CodingCharacter.h"
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
	/*if (!CurrentWeapon)
	{
		CurrentWeapon = NewWeapon;
		auto* Character = Cast<APZ_CodingCharacter>(GetOwner());
	    CurrentWeapon->SetOwner(GetOwner());
		CurrentWeapon->AttachToActor(Character, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("SocketWeapon")));
	//	CurrentWeapon->SetActorRelativeLocation(FVector{50,0,20});
	  	return true;
	}a
	return false;*/
	if (!CurrentWeapon && !NewWeapon->GetOwner())
	{	//return false;
		//return false;
	
		CurrentWeapon = NewWeapon;
		auto* Character = Cast<APZ_CodingCharacter>(GetOwner());
		
		//CurrentWeapon->SetOwner(GetOwner());
		CurrentWeapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
									FName(TEXT("SocketWeapon")));
		CurrentWeapon->SetActorRelativeLocation(FVector(-100,0,20));
		CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*	
        		
        		
        		
        		CurrentWeapon->AttachToActor(Character, FAttachmentTransformRules::KeepRelativeTransform,
        									FName(TEXT("SocketWeapon")));*/
		//CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//return true;
	}
	//return false;
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

