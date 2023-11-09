// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank.h"

ATank::ATank()
{

}

void ATank::SetMovingSpeed(float NewMovingSpeed)
{
	MovingSpeed = NewMovingSpeed;
}

void ATank::SetRotationSpeed(float NewRotationSpeed)
{
	RotationSpeed = NewRotationSpeed;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Tank"));
}
