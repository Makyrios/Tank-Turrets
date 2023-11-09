// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/TankSpawner.h"



void ATankSpawner::SetObjectData(TObjectPtr<APawnBase> SpawnActor)
{	
	Super::SetObjectData(SpawnActor);

	ATank* TankActor = Cast<ATank>(SpawnActor);
	if (TankActor)
	{
		TankActor->SetRotationSpeed(RotationSpeed);
		TankActor->SetMovingSpeed(MovingSpeed);
	}
}

