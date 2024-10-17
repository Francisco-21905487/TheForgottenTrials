// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheForgottenTrialsGameMode.h"
#include "TheForgottenTrialsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheForgottenTrialsGameMode::ATheForgottenTrialsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
