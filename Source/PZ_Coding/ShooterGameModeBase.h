// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PZ_CODING_API AShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AShooterGameModeBase();
	
UFUNCTION(BlueprintCallable, Category="UMG")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
