// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComp->SetSphereRadius(50.0f);
	SphereComp->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	SetRootComponent(SphereComp);


	MovementComp = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementCOmponent"));
	MovementComp->SetUpdatedComponent(SphereComp);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABasePawn::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ABasePawn::MoveRight);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABasePawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(FName("LookRight"), this, &ABasePawn::AddControllerYawInput);
}

void ABasePawn::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}

}

void ABasePawn::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}