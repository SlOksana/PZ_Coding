// Fill out your copyright notice in the Description page of Project Settings.


#include "KnifeWeapon.h"
#include "PZ_CodingCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

void AKnifeWeapon::InteractWeapon()
{
	
	ServerInteractCurrentWeapon();
}
void AKnifeWeapon::ServerInteractCurrentWeapon_Implementation()
{	FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Muzzle");
	FVector Forward = this->GetActorForwardVector();
	FVector LocationEnd = LocationSocket;
	
		FCollisionQueryParams RV_TraceParams;
		RV_TraceParams.bTraceComplex = true;
		FHitResult RV_Hit(ForceInit);
		FVector NewForward = Forward * Range;
		NewForward.Z += UKismetMathLibrary::RandomIntegerInRange(-200,200);
		NewForward.Y += UKismetMathLibrary::RandomIntegerInRange(-200,200);
		LocationEnd += NewForward;
			
		GetWorld()->LineTraceSingleByChannel(
		   RV_Hit,
		   LocationSocket,
		   LocationEnd,
		   ECC_Pawn,
		   RV_TraceParams
		);
	  	
		
		if (RV_Hit.bBlockingHit)
		{
			auto* Character = Cast<APZ_CodingCharacter>(RV_Hit.GetActor());
			if (Character)
			{Character->ApplyDamage();}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *RV_Hit.GetActor()->GetName());
		}
	
	}
	
	

