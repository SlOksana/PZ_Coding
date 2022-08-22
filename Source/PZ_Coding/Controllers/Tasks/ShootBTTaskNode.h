#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ShootBTTaskNode.generated.h"

UCLASS()
class PZ_CODING_API UShootBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UShootBTTaskNode();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
