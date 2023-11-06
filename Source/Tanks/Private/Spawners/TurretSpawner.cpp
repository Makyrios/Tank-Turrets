// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/TurretSpawner.h"


void ATurretSpawner::SpawnObject()
{	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnedActor = GetWorld()->SpawnActor<ATurret>(ActorToCreate, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
	if (SpawnedActor)
	{
		SetObjectData();
	}	
}

void ATurretSpawner::SetObjectData()
{
	SpawnedActor->SetFireRange(FireRange);
	SpawnedActor->SpawnDefaultController();
}

void ATurretSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnObject();
}
