#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskNodeClearBlackboardValue.generated.h"

UCLASS()
class PZ_CODING_API UBTTaskNodeClearBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTaskNodeClearBlackboardValue();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

};
