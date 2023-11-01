// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/TurretSpawner.h"

void ATurretSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnObject();
}

void ATurretSpawner::SpawnObject()
{	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnedActor = GetWorld()->SpawnActor<ATurret>(ACtorToCreate, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
	if (SpawnedActor)
	{
		SetObjectData();
	}	
}

void ATurretSpawner::SetObjectData()
{
	SpawnedActor->SetFireRange(FireRange);
}
