// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/TanksGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>

ATanksGameMode::ATanksGameMode()
{
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
