// Copyright Epic Games, Inc. All Rights Reserved.

#include "cpp3dpGameMode.h"
#include "cpp3dpCharacter.h"
#include "UObject/ConstructorHelpers.h"

Acpp3dpGameMode::Acpp3dpGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
