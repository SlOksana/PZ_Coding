#include "ShootBTTaskNode.h"
#include "PZ_Coding/PZ_CodingCharacter.h"
#include "AIController.h"
#include "PZ_Coding/ShooterCharacter.h"


UShootBTTaskNode::UShootBTTaskNode()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UShootBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
if(OwnerComp.GetOwner() == nullptr)
{
	return EBTNodeResult::Failed; 
}
	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter> (OwnerComp.GetAIOwner()->GetPawn());
	if(ShooterCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	ShooterCharacter->Shoot();
	return EBTNodeResult::Succeeded;
	
}
