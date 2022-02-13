#include "HealthBag.h"
AHealthBag::AHealthBag()
{
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

void AHealthBag::AddHealth(int32 Value)
{
	if(GetLocalRole() == ROLE_Authority )
	{
		if(CurrentHealth + Value > MaxHealth)
		{
			CurrentHealth = MaxHealth;
		}
		else
		{
			CurrentHealth +=Value;
		}

		UE_LOG(LogTemp, Display, TEXT("APZ_CodingCharacter::AddHealth: Currebt Health: %i"), CurrentHealth);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("APZ_CodingCharacter::AddHealth: AddHealth need to call from server only"));

	}
	
}

void AHealthBag::InteractItem(APZ_CodingCharacter* Character)
{
	Super::InteractItem(Character);
	Character->AddHealthServer(Health);
	Character->AddHealthClient(Health);
	
}
