// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/BaseSpawner.h"

#include "Engine/TargetPoint.h"

// Sets default values
ABaseSpawner::ABaseSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
}


void ABaseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseSpawner::SetObjectData()
{	
	if (SpawnedActor)
	{
		SpawnedActor->SetTowerRotationSpeed(TowerRotationSpeed);
		SpawnedActor->SetFireRange(FireRange);
		SpawnedActor->SetFireRate(FireRate);
		SpawnedActor->SpawnDefaultController();
		SpawnedActor->SetDamage(Damage);
	}
}

void ABaseSpawner::BeginPlay()
{	
	Super::BeginPlay();

	if (NumberToSpawn > SpawnPoints.Num())
	{
		NumberToSpawn = SpawnPoints.Num();
	}

	SpawnEnemies(ChoosePoints());
}

TArray<class ATargetPoint*> ABaseSpawner::ChoosePoints()
{
	TArray<class ATargetPoint*> SelectedPoints;

	while (SelectedPoints.Num() < NumberToSpawn)
	{
		int Temp_idx = FMath::RandRange(0, NumberToSpawn - 1);
		if (SpawnPoints.IsValidIndex(Temp_idx) && !SelectedPoints.Contains(SpawnPoints[Temp_idx]))
		{
			SelectedPoints.Push(SpawnPoints[Temp_idx]);
		}
	}
	return SelectedPoints;
}

void ABaseSpawner::SpawnEnemies(TArray<class ATargetPoint*> SelectedPoints)
{	
	for (auto& SpawnPoint : SelectedPoints)
	{
		if (SpawnPoint)
		{	
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnedActor = GetWorld()->SpawnActor<APawnBase>(ActorToCreate, SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation(), SpawnParams);
			SetObjectData();
		}
		else
		{
			return;
		}
	}
}



