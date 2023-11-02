// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/TankSpawner.h"


void ATankSpawner::SpawnObject()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnedActor = GetWorld()->SpawnActor<ATank>(ActorToCreate, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
	if (SpawnedActor)
	{
		SetObjectData();
	}
}

void ATankSpawner::SetObjectData()
{
	SpawnedActor->SetRotationSpeed(RotationSpeed);
	SpawnedActor->SetMovingSpeed(MovingSpeed);
	SpawnedActor->SpawnDefaultController();
}

void ATankSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnObject();
}
