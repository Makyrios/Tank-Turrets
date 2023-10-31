// Copyright Epic Games, Inc. All Rights Reserved.

#include "TanksGameMode.h"
#include "TanksCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATanksGameMode::ATanksGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
