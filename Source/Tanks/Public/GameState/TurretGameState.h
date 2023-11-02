// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TurretGameState.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATurretGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	int FindAllTanks() const;
	
};
