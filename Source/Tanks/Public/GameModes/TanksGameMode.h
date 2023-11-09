// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BaseGameMode.h"
#include "Controllers/BasePlayerController.h"
#include "GameState/TanksGameState.h"
#include "TanksGameMode.generated.h"

UCLASS(minimalapi)
class ATanksGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	ATanksGameMode();

	void HandleActorKilled(AActor* KilledActor) override;


protected:
	void BeginPlay() override;

	void HandleGameStart() override;

private:
	TObjectPtr<ATanksGameState> TanksGameState;

};



