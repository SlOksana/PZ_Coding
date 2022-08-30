#include "BTTaskNodeClearBlackboardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNodeClearBlackboardValue::UBTTaskNodeClearBlackboardValue()
{
	NodeName = "ClearBlackboardValue";
}

EBTNodeResult::Type UBTTaskNodeClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	 Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	return EBTNodeResult::Succeeded;
}

void UBTTaskNodeClearBlackboardValue::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
