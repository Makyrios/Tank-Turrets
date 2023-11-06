// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BaseGameMode.h"
#include "Actors/Tank.h"
#include "Actors/Turret.h"
#include <Kismet/GameplayStatics.h>


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
	StartGame();

	if (PlayerController != nullptr)
	{
		PlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
			PlayerController,
			&ABasePlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			TimerDelegate,
			StartGameDelay,
			false
		);
	}
}
