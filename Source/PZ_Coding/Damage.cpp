#include "Damage.h"

int32 HealthNumber = 100;

ADamage::ADamage()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	bHealth = false;
}

void ADamage::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADamage::BoxBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ADamage::BoxEndOverlap);
	Damage.AddUFunction(this, "HealthDamage");
}

void ADamage::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
	 bFromSweep, const FHitResult& SweepResult)
{
	GetWorldTimerManager().SetTimer(DamageTimer, this, &ADamage::Health,
		1.f, true, -1);

}

void ADamage::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	if (bHealth)
	{
		GetWorldTimerManager().PauseTimer(DamageTimer);
	}
	bHealth = false;
}

void ADamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADamage::HealthDamage(){}

void ADamage::Health()
{
	Damage.Broadcast();
	FString str1 = "Damage ";
	HealthNumber -=2;
	str1 = str1 + FString::FromInt(HealthNumber);
		
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, str1);
	bHealth = true;
}