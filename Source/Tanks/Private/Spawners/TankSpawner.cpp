// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/TankSpawner.h"

void ATankSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnObject();
}

void ATankSpawner::SpawnObject()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnedActor = GetWorld()->SpawnActor<ATank>(ACtorToCreate, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
	if (SpawnedActor)
	{
		SetObjectData();
	}
}

void ATankSpawner::SetObjectData()
{
	SpawnedActor->SetRotationSpeed(RotationSpeed);
	SpawnedActor->SetMovingSpeed(MovingSpeed);
}
