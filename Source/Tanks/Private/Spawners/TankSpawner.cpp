// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/TankSpawner.h"



void ATankSpawner::SetObjectData()
{	
	Super::SetObjectData();
	SpawnedActor->SetRotationSpeed(RotationSpeed);	
	SpawnedActor->SetMovingSpeed(MovingSpeed);	
}

