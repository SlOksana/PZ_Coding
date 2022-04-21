#include "BTService_PlayerLocationIfSeen.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = "UpdatePlayerLocationIfSeen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//if(PlayerPawn->GetNetMode() == NM_Standalone)
	//{
		if(PlayerPawn == nullptr)
		{
			return;
		}

		if(OwnerComp.GetAIOwner() == nullptr)
		{
			return;
		}

		if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
		
		}

		else
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}
	}
//}
	void UBTService_PlayerLocationIfSeen::OnGameplayTaskActivated(UGameplayTask& Task)
	{
		Super::OnGameplayTaskActivated(Task);
	}

	void UBTService_PlayerLocationIfSeen::OnGameplayTaskDeactivated(UGameplayTask& Task)
	{
		Super::OnGameplayTaskDeactivated(Task);
	}
