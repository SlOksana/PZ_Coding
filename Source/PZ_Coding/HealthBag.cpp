#include "HealthBag.h"
AHealthBag::AHealthBag()
{
    CurrentHealth = 10;
	
}

void AHealthBag::InteractItem(APZ_CodingCharacter* Character)
{
	Super::InteractItem(Character);
Character->AddHealth(CurrentHealth);
	
}
