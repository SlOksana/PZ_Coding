#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

UCLASS()
class PZ_CODING_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
 AShooterAIController();
	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* Behavior;
	
	virtual void BeginPlay() override;
public:
	virtual FGenericTeamId GetGenericTeamId() const override;


};
