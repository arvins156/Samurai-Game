// Copyright Epic Games, Inc. All Rights Reserved.

#include "SamuraiGameGameMode.h"
#include "UObject/ConstructorHelpers.h"

void ASamuraiGameGameMode::PawnKilled(APawn* PawnKilled)
{
<<<<<<< Updated upstream
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SamuraiGame/BP_SamuraiCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("NOT FOUND"));
		}
	}
}
=======
	
}
>>>>>>> Stashed changes
