#include "HealthBag.h"
AHealthBag::AHealthBag()
{
    Health = 10;
	
}

void AHealthBag::InteractItem(APZ_CodingCharacter* Character)
{
	Super::InteractItem(Character);
	Character->AddHealth(Health);
	
}
