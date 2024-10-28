// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SamuraiGameGameMode.generated.h"

UCLASS()
class SAMURAIGAME_API ASamuraiGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	virtual void PawnKilled(APawn* PawnKilled);
};



