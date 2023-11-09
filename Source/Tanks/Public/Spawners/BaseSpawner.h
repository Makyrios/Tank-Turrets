// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Actors/PawnBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.generated.h"


UCLASS()
class TANKS_API ABaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpawner();
	

	virtual void Tick(float DeltaTime) override;
	virtual void SetObjectData(TObjectPtr<APawnBase> SpawnActor);
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawned Object Settings")
	TSubclassOf <APawnBase> ActorToCreate;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Spawned Object Settings")
	float FireRange{ 2000.f };

	UPROPERTY(EditAnywhere, Category = "Spawned Object Settings")
	float FireRate{ 2.f };

	UPROPERTY(EditAnywhere, Category = "Spawned Object Settings")
	float TowerRotationSpeed{ 10.f };

	UPROPERTY(EditAnywhere, Category = "Spawned Object Settings")
	float Damage{ 10.f };

	UPROPERTY(EditAnywhere, Category = "Spawned Object Settings")
	float HealthBarVisibilityRange{ 1500.f };

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	TArray<class ATargetPoint*> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	int NumberToSpawn{ 1 };

private:
	

	TArray<class ATargetPoint*> ChoosePoints();
	void SpawnEnemies(TArray<class ATargetPoint*> SelectedPoints);
};
