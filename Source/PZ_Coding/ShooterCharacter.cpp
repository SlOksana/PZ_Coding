#include "ShooterCharacter.h"
#include "WeaponManagerComponent.h"

AShooterCharacter::AShooterCharacter()
{
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterCharacter::Shoot() const
{
	if(GetWeaponManagerComponent())
	{
		GetWeaponManagerComponent()->InteractCurrentWeapon();
	}
}
