// Copyright Epic Games, Inc. All Rights Reserved.

#include "PZ_CodingGameMode.h"
#include "PZ_CodingCharacter.h"
#include "UObject/ConstructorHelpers.h"

APZ_CodingGameMode::APZ_CodingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
