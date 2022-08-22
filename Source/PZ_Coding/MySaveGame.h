#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

UCLASS()
class PZ_CODING_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic )
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	float PlayerHealth;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector PlayerPosition;
	UMySaveGame(); 
};
