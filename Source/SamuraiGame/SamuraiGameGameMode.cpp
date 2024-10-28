// Copyright Epic Games, Inc. All Rights Reserved.

#include "SamuraiGameGameMode.h"
#include "UObject/ConstructorHelpers.h"

void ASamuraiGameGameMode::PawnKilled(APawn* PawnKilled)
{
<<<<<<< Updated upstream
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
=======
	
}
>>>>>>> Stashed changes
