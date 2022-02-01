// Copyright Epic Games, Inc. All Rights Reserved.

#include "PZ_CodingCharacter.h"
#include "Projectile.h"
#include "WeaponManagerComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/SkeletalMeshSocket.h"


APZ_CodingCharacter::APZ_CodingCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

// set our turn rates for input
BaseTurnRate = 45.f;
BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
bUseControllerRotationPitch = false;
bUseControllerRotationYaw = false;
bUseControllerRotationRoll = false;

	// Configure character movement
GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	WeaponManagerComp = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("WeaponManagerComponent"));

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	APZ_CodingCharacter::Inventory();

}
bool APZ_CodingCharacter::CheckIsAndroid()
{
#if PLATFORM_ANDROID
	return true;
#endif
	return false;
}
void APZ_CodingCharacter::Inventory()
{
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

UInventoryComponent* APZ_CodingCharacter::GetInventory()
{
	return InventoryComp;
	
}

void APZ_CodingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
//	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

//	PlayerInputComponent->BindAxis("MoveForward", this, &APZ_CodingCharacter::MoveForward);
//	PlayerInputComponent->BindAxis("MoveRight", this, &APZ_CodingCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
//	PlayerInputComponent->BindAxis("TurnRate", this, &APZ_CodingCharacter::TurnAtRate);
//	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
//	PlayerInputComponent->BindAxis("LookUpRate", this, &APZ_CodingCharacter::LookUpAtRate);

	// handle touch devices
	//PlayerInputComponent->BindTouch(IE_Pressed, this, &APZ_CodingCharacter::TouchStarted);
	//PlayerInputComponent->BindTouch(IE_Released, this, &APZ_CodingCharacter::TouchStopped);

	// VR headset functionality
	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &APZ_CodingCharacter::OnResetVR);
//	PlayerInputComponent->BindAction("ForwardHeightTrace", IE_Pressed, this, &APZ_CodingCharacter::ForwardHeightTrace);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponManagerComp, &UWeaponManagerComponent::ReloadCurrentWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponManagerComp, &UWeaponManagerComponent::InteractCurrentWeapon);
	PlayerInputComponent->BindAction("DropDownWeapon", IE_Pressed, this, &APZ_CodingCharacter::OnDropWeapon);

}
void APZ_CodingCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health.
	DOREPLIFETIME(APZ_CodingCharacter, CurrentHealth);
	
}

void APZ_CodingCharacter::OnRep_CurrentHealth()
{
	OnHealth_Update();
}
void APZ_CodingCharacter::OnHealth_Update()
{
	if(IsLocallyControlled())
	{
	   FString healthMessage=FString::Printf(TEXT("You now have %f health remaining."),CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,healthMessage);

		if(CurrentHealth<=0)
		{
			FString deathMessage=FString::Printf(TEXT("You have been killed"));
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, deathMessage);
		}
	}

	if(GetLocalRole()==ROLE_Authority)
	{
		FString healthMessage=FString::Printf(TEXT("%s now have %f health remainig."), *GetFName().ToString(),CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue, healthMessage);
	}
}

void APZ_CodingCharacter::OnDropWeapon()
{
	WeaponManagerComp->DropCurrentWeapon();
}

void APZ_CodingCharacter::SetCurrentHealth(float healthValue)
{
	if(GetLocalRole()==ROLE_Authority)
	{
		CurrentHealth = FMath::Clamp(healthValue, 0.0f, MaxHealth);
		OnHealth_Update();
	}
}

float APZ_CodingCharacter::TakeDamage(float DamageTaken, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageApplied = CurrentHealth - DamageTaken;
	SetCurrentHealth(damageApplied);
	return  damageApplied;
}

/*void APZ_CodingCharacter::OnResetVR()
{
	// If PZ_Coding is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in PZ_Coding.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}
*/
/*void APZ_CodingCharacter::ForwardHeightTrace()
{

	ServerForwardHeightTrace();
	
}/*

/*void APZ_CodingCharacter::ServerForwardHeightTrace_Implementation()
{
	if (IsClimbing)	{return;}
	FHitResult ForwardT;
	FCollisionQueryParams CollisionQueryParams;
	GetWorld()->LineTraceSingleByChannel(ForwardT,GetActorLocation(),GetActorLocation()+(GetActorForwardVector()*150.0f),
		ECC_Visibility, CollisionQueryParams);
	GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Cyan,"ForwardTrace");

	FHitResult HeightT;
	FVector StartVector = GetActorLocation()+FVector(0,0, 500.0f) + (GetActorForwardVector()*75.0f);
	FVector EndVector = GetActorLocation()+(GetActorForwardVector()* 75.0f);
	GetWorld()->LineTraceSingleByChannel(HeightT,StartVector,EndVector,ECC_Visibility, CollisionQueryParams );
	GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Cyan,"HeightTrace");

	
	
	FVector FWallLocation = HeightT.Location;
	FVector FWallNormal = ForwardT.Normal;
	FVector FWallForwLocation = ForwardT.Location;
	FVector HipsSocketVector = GetMesh()->GetSocketLocation("HipsSocket");

	IsClimbing = true;
	
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	GetCharacterMovement()->StopMovementImmediately();

	MulticastClimbAnim();


	FTimerHandle ClimbTimer;
	GetWorldTimerManager().SetTimer(ClimbTimer, [this]
	{
		IsClimbing = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}, AnimMontageClimb->SequenceLength, false);

	}*/
void APZ_CodingCharacter::MulticastClimbAnim_Implementation()
{
	float CompletedIn = PlayAnimMontage(AnimMontageClimb,1.f,NAME_None);
}
void APZ_CodingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}



/*
void APZ_CodingCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}
void APZ_CodingCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	
		StopJumping();
	}
void APZ_CodingCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APZ_CodingCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APZ_CodingCharacter::MoveForward(float Value)
{
	if(IsClimbing)
	{
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}
void APZ_CodingCharacter::MoveRight(float Value)
{
	if(IsClimbing)
	{
		if ( (Controller != nullptr) && (Value != 0.0f) )
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
	
			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}*/
