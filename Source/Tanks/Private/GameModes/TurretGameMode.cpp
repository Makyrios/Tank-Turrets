// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/TurretGameMode.h"

ATurretGameMode::ATurretGameMode()
{
}

void ATurretGameMode::HandleActorKilled(AActor* KilledActor)
{
	Super::HandleActorKilled(KilledActor);

	if (KilledActor->ActorHasTag("Tank"))
	{
		StopGame(false);
	}
	else if (KilledActor->ActorHasTag("Turret"))
	{
		if (TurretGameState != nullptr)
		{
			if (TurretGameState->FindAllTanks() - 1 <= 0)
			{
				StopGame(true);
			}
		}
	}
}

void ATurretGameMode::BeginPlay()
{
	Super::BeginPlay();

	TurretGameState = Cast<ATurretGameState>(GameState);

}

void ATurretGameMode::HandleGameStart()
{
	Super::HandleGameStart();

}
