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
	
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UPawnSensingComponent* PawnSensingComponent;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION()
	void Shoot() const;
	UFUNCTION()
	void OnSeePawn(APawn* OtherPawn);
	UFUNCTION()
	void OnHearPawn(APawn* OtherActor, const FVector &Location, float Volume);
	
};
