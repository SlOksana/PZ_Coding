#include "MainCharacterC.h"

AMainCharacterC::AMainCharacterC()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void AMainCharacterC::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(100);

	GetWorldTimerManager().SetTimer(TimerDamage, this, &ThisClass::RepeatingFunctionDamage, 1.0f, true, 2.0f);
	GetWorldTimerManager().SetTimer(TimerHealth, this, &ThisClass::RepeatingFunctionDamage, 2.0f, true, 2.0f);

	DestroyActor.AddUFunction(this, "DestroyA");
	DamageActor.AddUFunction(this, "DamageA");
}


void AMainCharacterC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AMainCharacterC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacterC::SetHealth(int32 CurrentHealth)
{
	FString str1 = "Current Health of Main Character ";
	str1 = str1 + FString::FromInt(CurrentHealth);
	Health = CurrentHealth;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, str1);

	FString str2 =  "Current Health of Another Character ";
	str2 = str2 + FString::FromInt(CurrentHealth);
	Health = CurrentHealth;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, str2);
}

int32 AMainCharacterC::GetRestorationHealth()
{
	
	return Health;
}

int32 AMainCharacterC::GetHealth()
{
	
	return Health;
}

void AMainCharacterC::DestroyA()
{
	
	Destroy();

}

void AMainCharacterC::DamageA()
{
	if (GetHealth() > 0)
	{
		SetHealth(GetHealth() - 10);
	}

}

void AMainCharacterC::RepeatingFunctionDamage()
{
	if (GetHealth() > 0)
	{
		SetHealth(GetHealth() - 10);
		DamageActor.Broadcast();
	}
	
	if (GetHealth() < 100)
	{
		SetHealth(GetHealth() + 3);
	}
	if (GetHealth() > 100 || GetHealth() < 0)
	{
		GetWorldTimerManager().ClearTimer(TimerDamage);
		GetWorldTimerManager().ClearTimer(TimerHealth);
		DestroyActor.Broadcast();

	}
}



