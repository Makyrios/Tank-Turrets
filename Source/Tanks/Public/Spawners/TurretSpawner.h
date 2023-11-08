// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Actors/Turret.h"
#include "CoreMinimal.h"
#include "Spawners/BaseSpawner.h"
#include "TurretSpawner.generated.h"

/**
 * 
 */

UCLASS()
class TANKS_API ATurretSpawner : public ABaseSpawner
{
	GENERATED_BODY()

private:
	TObjectPtr<ATurret> SpawnedActor;

	TSubclassOf<ATurret> ActorToCreate;
};
