// Copyright Epic Games, Inc. All Rights Reserved.

#include "SamuraiGameGameMode.h"
#include "SamuraiGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASamuraiGameGameMode::ASamuraiGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
