// Copyright Epic Games, Inc. All Rights Reserved.

#include "SamuraiGameGameMode.h"
#include "SamuraiGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASamuraiGameGameMode::ASamuraiGameGameMode()
{
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
