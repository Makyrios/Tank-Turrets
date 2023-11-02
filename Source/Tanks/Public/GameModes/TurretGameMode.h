// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BaseGameMode.h"
#include <Controllers/PlayerControllerBase.h>
#include "GameState/TurretGameState.h"
#include "TurretGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATurretGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	ATurretGameMode();

	void HandleActorKilled(AActor* KilledActor) override;


protected:
	void BeginPlay() override;
	void HandleGameStart();

private:
	// Change to turret player controller
	TObjectPtr<APlayerControllerBase> TurretPlayerController;
	TObjectPtr<ATurretGameState> TurretGameState;
	
};
