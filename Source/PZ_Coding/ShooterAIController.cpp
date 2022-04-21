#include "ShooterAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/PawnSensingComponent.h"

AShooterAIController::AShooterAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if(Behavior != nullptr)
	{
		RunBehaviorTree(Behavior);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

FGenericTeamId AShooterAIController::GetGenericTeamId() const
{
	return FGenericTeamId(1);
}
