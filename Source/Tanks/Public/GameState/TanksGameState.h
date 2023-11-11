// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameState/BaseGameState.h"
#include "TanksGameState.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATanksGameState : public ABaseGameState
{
	GENERATED_BODY()

public:
	virtual int FindAllEnemies() const override;
	virtual EEnemyType GetEnemyType() const { return EEnemyType::Turret; }
};
