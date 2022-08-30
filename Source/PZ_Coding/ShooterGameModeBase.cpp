// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"

AShooterGameModeBase::AShooterGameModeBase()
{
}

void AShooterGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if(CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if( NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if(CurrentWidget != nullptr)
		{
			CurrentWidget -> AddToViewport();
		}
		
	}
	
}

void AShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

