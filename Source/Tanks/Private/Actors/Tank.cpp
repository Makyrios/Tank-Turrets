// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank.h"
#include "GameFramework/FloatingPawnMovement.h"
#include <Kismet/GameplayStatics.h>

ATank::ATank()
{
	FloatingMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement Component"));
	FloatingMovementComponent->MaxSpeed = MovingSpeed;
}

void ATank::SetMovingSpeed(float NewMovingSpeed)
{
	MovingSpeed = NewMovingSpeed;
	FloatingMovementComponent->MaxSpeed = NewMovingSpeed;
}

void ATank::SetRotationSpeed(float NewRotationSpeed)
{
	RotationSpeed = NewRotationSpeed;
}

void ATank::RotateBase(FRotator Rotation)
{
	Rotation.Pitch = 0;
	Rotation.Roll = 0;
	MeshBase->SetWorldRotation(FMath::RInterpTo(MeshBase->GetComponentRotation(), Rotation,
		GetWorld()->GetDeltaSeconds(), RotationSpeed));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Tank"));
}
