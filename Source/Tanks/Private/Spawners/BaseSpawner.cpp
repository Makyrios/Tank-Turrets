// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/BaseSpawner.h"

// Sets default values
ABaseSpawner::ABaseSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned


// Called every frame
void ABaseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


