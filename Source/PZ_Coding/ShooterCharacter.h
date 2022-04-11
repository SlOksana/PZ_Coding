#pragma once

#include "CoreMinimal.h"
#include "PZ_CodingCharacter.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class PZ_CODING_API AShooterCharacter : public APZ_CodingCharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();
	virtual void BeginPlay() override;
	UFUNCTION()
	void Shoot() const;
	
};
