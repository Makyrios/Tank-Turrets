// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TanksGameState.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATanksGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	int TurretAmount;

protected:
	void HandleBeginPlay() override;

private:
	void FindAllTurrets();
	
};
