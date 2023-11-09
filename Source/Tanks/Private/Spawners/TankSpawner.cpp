// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/TankSpawner.h"



void ATankSpawner::SetObjectData()
{	
	Super::SetObjectData();
	if (SpawnedActor)
	{
		SpawnedActor->SetRotationSpeed(RotationSpeed);	
		SpawnedActor->SetMovingSpeed(MovingSpeed);	
	}
}

