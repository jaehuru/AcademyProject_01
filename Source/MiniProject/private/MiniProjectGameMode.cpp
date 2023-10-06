// Copyright Epic Games, Inc. All Rights Reserved.

#include "MiniProjectGameMode.h"
#include "MiniProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMiniProjectGameMode::AMiniProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
