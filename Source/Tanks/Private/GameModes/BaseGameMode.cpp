// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BaseGameMode.h"
#include "Actors/Tank.h"
#include "Actors/Turret.h"
#include <Kismet/GameplayStatics.h>


ABaseGameMode::ABaseGameMode()
{

}

void ABaseGameMode::HandleActorKilled(AActor* KilledActor)
{
	if (KilledActor != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("%s actor is killed"), *KilledActor->GetActorNameOrLabel());
	}
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();

}

void ABaseGameMode::HandleGameStart()
{
	FTimerHandle StartGameTimerHandle;
	GetWorldTimerManager().SetTimer(StartGameTimerHandle, [&]() 
		{ if (OnGameStart.IsBound()) OnGameStart.Broadcast(); }, StartGameDelay, false);

}
