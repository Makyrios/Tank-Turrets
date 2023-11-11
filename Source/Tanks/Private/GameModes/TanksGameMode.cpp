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
		OnGameEnd.Clear();
	}
	else if (KilledActor->ActorHasTag("Turret"))
	{
		OnEnemyKilled.Broadcast();
		if (TanksGameState != nullptr)
		{
			if (TanksGameState->FindAllEnemies() <= 0)
			{
				OnGameEnd.Broadcast(true);
				OnGameEnd.Clear();
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
