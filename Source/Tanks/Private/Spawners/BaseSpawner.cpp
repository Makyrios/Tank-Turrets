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

void ABaseSpawner::SetObjectData(TObjectPtr<APawnBase> SpawnActor)
{	
	if (SpawnActor)
	{
		SpawnActor->SetTowerRotationSpeed(TowerRotationSpeed);
		SpawnActor->SetFireRange(FireRange);
		SpawnActor->SetFireRate(FireRate);
		SpawnActor->SetDamage(Damage);
		SpawnActor->SetHealthBarVisibilityRange(HealthBarVisibilityRange);
		SpawnActor->SpawnDefaultController();
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
		int TempIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		if (SpawnPoints.IsValidIndex(TempIndex) && !SelectedPoints.Contains(SpawnPoints[TempIndex]))
		{
			SelectedPoints.Push(SpawnPoints[TempIndex]);
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
			APawnBase* SpawnActor = GetWorld()->SpawnActor<APawnBase>(ActorToCreate, SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation(), SpawnParams);
			SetObjectData(SpawnActor);
		}
		else
		{
			return;
		}
	}
}



