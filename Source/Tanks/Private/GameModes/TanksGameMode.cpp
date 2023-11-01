// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/TanksGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>

ATanksGameMode::ATanksGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATanksGameMode::HandleTankKilled()
{
	StopGame(false);
}

void ATanksGameMode::HandleTurretKilled()
{
	if (TanksGameState != nullptr)
	{
		if (--TanksGameState->TurretAmount <= 0)
		{
			StopGame(true);
		}
	}
}

void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	TanksPlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	TanksGameState = Cast<ATanksGameState>(GameState);

	HandleGameStart();
}

void ATanksGameMode::HandleGameStart()
{
	StartGame();

	if (TanksPlayerController != nullptr)
	{
		TanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
			TanksPlayerController,
			&APlayerControllerBase::SetPlayerEnabledState,
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
