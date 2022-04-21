// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeActor.h"

// Sets default values
ACubeActor::ACubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetLife(100);

}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestroyCude, this, &ThisClass::DestroyCudeFunction, 1.0f, true, 2.0f);
}
void ACubeActor::SetLife(int32 CurrentLife)
{
	Life = CurrentLife;

}

int32 ACubeActor::GetLife()
{
	return Life;
}

void ACubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeActor::DestroyCudeFunction()
{
	if (GetLife() > 0)
	{
		SetLife(GetLife() - 10);
	}
	if (GetLife() < 35)
	{
		Destroy();
	}
	
}

