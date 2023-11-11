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
		OnGameEnd.Broadcast(false);
	}
	else if (KilledActor->ActorHasTag("Turret"))
	{
		if (TanksGameState != nullptr)
		{
			if (TanksGameState->FindAllTurrets() - 1 <= 0)
			{
				OnGameEnd.Broadcast(true);
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
