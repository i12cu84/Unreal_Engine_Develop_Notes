// Copyright Epic Games, Inc. All Rights Reserved.

#include "MNTaskGameMode.h"
#include "MNTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMNTaskGameMode::AMNTaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
