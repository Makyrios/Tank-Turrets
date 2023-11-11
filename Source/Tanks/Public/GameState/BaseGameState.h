// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseGameState.generated.h"


UENUM()
enum EEnemyType
{
	Tank,
	Turret
};

UCLASS(Abstract)
class TANKS_API ABaseGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	virtual int FindAllEnemies() const PURE_VIRTUAL(&ABaseGameState::FindAllEnemies, return 0;);
	UFUNCTION(BlueprintCallable)
	virtual EEnemyType GetEnemyType() const PURE_VIRTUAL(&ABaseGameState::GetEnemyType, return EEnemyType::Turret;);
	
};
