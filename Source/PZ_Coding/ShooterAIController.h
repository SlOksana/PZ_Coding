#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

UCLASS()
class PZ_CODING_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* Behavior;
	virtual void BeginPlay() override;
};
