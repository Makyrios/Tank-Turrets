// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/TurretSpawner.h"


void ATurretSpawner::SpawnObject()
{	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnedActor = GetWorld()->SpawnActor<ATurret>(ActorToCreate, GetActorLocation(), FRotator::ZeroRotator);
	
	if (SpawnedActor)
	{
		SetObjectData();
	}	
}

void ATurretSpawner::SetObjectData()
{
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	SpawnedActor->SetFireRange(FireRange);
	SpawnedActor->SetFireRate(FireRate);
	SpawnedActor->SetTowerRotationSpeed(TowerRotationSpeed);
	SpawnedActor->SpawnDefaultController();
	SpawnedActor->SetActorRotation(GetActorRotation());
}

void ATurretSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnObject();
}
