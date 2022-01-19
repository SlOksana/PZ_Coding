#include "Cube_PZ_8.h"
#include "Cube.h"
#include "Chaos/Collision/CollisionApplyType.h"


ACube_PZ_8::ACube_PZ_8()
{
	
	PrimaryActorTick.bCanEverTick = true;

}

FVector ACube_PZ_8::Position()
{
	const FVector Position(rand() % 1000 + 1.f, rand() % 1000 + 1.f, rand() % 1000 + 1);
	return Position;
	
}

FRotator ACube_PZ_8::Rotation()
{
	const FRotator Rotation(0.f, 0.f, 0.f);
	return Rotation;
}

void ACube_PZ_8::NewCubeCreator()
{
	NewCube(AmountOfCubes);
}

void ACube_PZ_8::NewCube(int32 value)
{
	for (int32 i = 0; i < value; i++)
	{
	
		ACube* NewCube = GetWorld()->SpawnActor<ACube>(Position(), Rotation());
		CubeArray.Add(NewCube);
	}
	GetWorldTimerManager().SetTimer(DestroyCubeTimer,this,&ThisClass::DestroyCube,5.0f,false);
	
	
}
void ACube_PZ_8::DestroyCube()
{
	for(ACube* Cube:CubeArray)
	{
		Cube->Destroy();
	}
}


// Called when the game starts or when spawned
void ACube_PZ_8::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::FromInt(AmountOfCubes));
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::FromInt(CubeArray.Num()));
	GetWorldTimerManager().SetTimer(CubeTimer, this, &ThisClass::NewCubeCreator, 1.0f, false);
	
}

// Called every frame
void ACube_PZ_8::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
