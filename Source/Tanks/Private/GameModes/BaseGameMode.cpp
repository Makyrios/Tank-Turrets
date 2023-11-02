// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BaseGameMode.h"
#include "Actors/Tank.h"
#include "Actors/Turret.h"


void ABaseGameMode::HandleActorKilled(AActor* KilledActor)
{
	if (KilledActor != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("%s actor is killed"), *KilledActor->GetActorNameOrLabel());
	}

}


void ABaseGameMode::HandleGameStart()
{
	StartGame();
}
