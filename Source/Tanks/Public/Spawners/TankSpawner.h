// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Actors/Tank.h"
#include "CoreMinimal.h"
#include "Spawners/BaseSpawner.h"
#include "TankSpawner.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankSpawner : public ABaseSpawner
{
	GENERATED_BODY()
public:
	virtual void SpawnObject() override;
	virtual void SetObjectData() override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	TObjectPtr<ATank> SpawnedActor;

	UPROPERTY(EditDefaultsOnly, Category = "Spawned Object Settings")
	TSubclassOf<ATank> ActorToCreate;

	UPROPERTY(EditAnywhere, Category = "Spawned Object Settings")
	float MovingSpeed{ 20.f };

	UPROPERTY(EditAnywhere, Category = "Spawned Object Settings")
	float RotationSpeed{ 20.f };




};
