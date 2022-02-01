// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManagerComponent.h"
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
bool UWeaponManagerComponent::SetCurrentWeapon(ABaseWeapon* NewWeapon)
{
	if (!CurrentWeapon)
	{
		CurrentWeapon = NewWeapon;
		auto* Character = Cast<APZ_CodingCharacter>(GetOwner());
		CurrentWeapon->SetOwner(GetOwner());
		CurrentWeapon->AttachToActor(Character, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("SocketWeapon")));
		return true;
	}
	return false;

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
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		auto* Character = Cast<APZ_CodingCharacter>(GetOwner());
		const FVector NewLocation = Character->GetMesh()->GetRightVector() * DistanceToDropWeapon + Character->GetMesh()->GetComponentLocation();
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

