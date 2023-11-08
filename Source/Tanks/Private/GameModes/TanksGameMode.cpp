// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/TanksGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>

ATanksGameMode::ATanksGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATanksGameMode::HandleActorKilled(AActor* KilledActor)
{
	Super::HandleActorKilled(KilledActor);

	if (KilledActor->ActorHasTag("Player"))
	{
		StopGame(false);
	}
	else if (KilledActor->ActorHasTag("Turret"))
	{
		if (TanksGameState != nullptr)
		{
			if (TanksGameState->FindAllTurrets() - 1 <= 0)
			{
				StopGame(true);
			}
		}
	}
}


void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	TanksGameState = Cast<ATanksGameState>(GameState);
}

void ATanksGameMode::HandleGameStart()
{
	Super::HandleGameStart();

}
