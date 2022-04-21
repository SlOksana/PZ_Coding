#include "ShooterCharacter.h"

#include "ShooterAIController.h"
#include "WeaponManagerComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"

AShooterCharacter::AShooterCharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensingComponent->SetPeripheralVisionAngle(90.0f);
	

}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ThisClass::OnSeePawn);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &ThisClass::OnHearPawn);
}

void AShooterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AShooterCharacter::Shoot() const
{
	
	if(GetWeaponManagerComponent())
	{
		
		GetWeaponManagerComponent()->InteractCurrentWeapon();
	}
}

void AShooterCharacter::OnSeePawn(APawn* OtherPawn)
{
	auto* AIController = Cast<AShooterAIController>(GetController());
	if (AIController)
	{

		AIController->GetBlackboardComponent()->ClearValue(TEXT("Noise"));
		AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("Player"),OtherPawn);
		AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),OtherPawn->GetActorLocation());
		
	
	}
}
void AShooterCharacter::OnHearPawn(APawn* OtherActor, const FVector& Location, float Volume)
{
	
	const FString VolumeDes = FString::Printf(TEXT("at volume %f"), Volume);
	FString message = TEXT("Heard Actor ") + OtherActor->GetName() + VolumeDes;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Red, message);
	auto* AIController = Cast<AShooterAIController>(GetController());
	if(AIController)
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("Noise"),Location);
	}
	
}
