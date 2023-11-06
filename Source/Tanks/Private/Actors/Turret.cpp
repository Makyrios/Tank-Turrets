// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Turret.h"
#include "Kismet/GameplayStatics.h"



ATurret::ATurret()
{
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Turret"));
}


