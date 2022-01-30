// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManagerComponent.h"

#include "PZ_CodingCharacter.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
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

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

