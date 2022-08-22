// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxCollisionC.h"

// Sets default values
ABoxCollisionC::ABoxCollisionC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollisionComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxCollisionComponent"));
	BoxCollisionComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ABoxCollisionC::BeginPlay()
{
	Super::BeginPlay();
	BoxCollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::PrimitiveComponent);
	OnHitMulticast.AddDynamic(this, &ThisClass::MulticastEvent);
	OnHitDynamic.BindUFunction(this, "NewLocation");
	OnHitMulticast.Add(OnHitDynamic);
}

// Called every frame
void ABoxCollisionC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABoxCollisionC::NewLocation()
{
	FVector vector(100,0,0);
	BoxCollisionComponent->AddWorldOffset(vector);
 }

void ABoxCollisionC::PrimitiveComponent(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OnHitMulticast.IsBound())
	{
		OnHitMulticast.Broadcast();
	}
}