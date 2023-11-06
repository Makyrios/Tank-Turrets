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
public:
	virtual void SpawnObject() override;
	virtual void SetObjectData() override;

protected:
	virtual void BeginPlay() override;
	
private:
	TObjectPtr<ATurret> SpawnedActor;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawned Object Settings")
	TSubclassOf<ATurret> ActorToCreate;


};
