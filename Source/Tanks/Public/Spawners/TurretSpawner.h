// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Turret.h"

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
	ATurret* SpawnedActor;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawned Object Settings")
	TSubclassOf <ATurret> ACtorToCreate;

	UPROPERTY(EditAnywhere, Category = "Spawned Object Settings")
	float FireRange{ 2000.f };

protected:
	virtual void BeginPlay() override;

public:
	virtual void SpawnObject() override;
	virtual void SetObjectData() override;
};
