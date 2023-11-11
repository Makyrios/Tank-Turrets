// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameState/BaseGameState.h"
#include "TurretGameState.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATurretGameState : public ABaseGameState
{
	GENERATED_BODY()

public:
	virtual int FindAllEnemies() const override;
	inline virtual EEnemyType GetEnemyType() const { return EEnemyType::Tank; }
};
