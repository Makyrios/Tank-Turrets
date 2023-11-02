// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Controllers/PlayerControllerBase.h"
#include "GameState/TanksGameState.h"
#include "TanksGameMode.generated.h"

UCLASS(minimalapi)
class ATanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartGameDelay = 2;

	ATanksGameMode();

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void StopGame(bool bPlayerWon);

	void HandleTankKilled();
	void HandleTurretKilled();


protected:
	void BeginPlay() override;

private:
	TObjectPtr<APlayerControllerBase> TanksPlayerController;
	TObjectPtr<ATanksGameState> TanksGameState;


	void HandleGameStart();
};



