// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TankAIController.h"
#include "NavigationSystem.h"
#include <Kismet/GameplayStatics.h>

void ATankAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TankPawn = Cast<ATank>(InPawn);
}

void ATankAIController::ExecuteTasks(float DeltaTime)
{
	Super::ExecuteTasks(DeltaTime);

	SetRandomMoveLocation(DeltaTime);
	UE_LOG(LogTemp, Display, TEXT("%f %f %f"), MoveLocation.X, MoveLocation.Y, MoveLocation.Z);
	
}

void ATankAIController::SetRandomMoveLocation(float DeltaTime)
{
	// If MoveToLocation is empty set new point and start moving to it
	if (FVector::PointsAreNear(TankPawn->GetActorLocation(), MoveLocation, 2))
	{
		// Set new point
		FindMoveToLocation(UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation(), 1500);
	}
	// Move to point
	MoveToLocation(MoveLocation, DeltaTime);
}

void ATankAIController::FindMoveToLocation(const FVector& Point, float Radius)
{
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, Point, MoveLocation, Radius);
}

void ATankAIController::MoveToLocation(const FVector& Location, float DeltaTime)
{
	// Rotate to
	FRotator DirToMoveRot = (Location - TankPawn->GetActorLocation()).Rotation();
	FRotator CurrentRotation = TankPawn->GetActorRotation();
	TankPawn->SetActorRotation(FMath::RInterpConstantTo(CurrentRotation, DirToMoveRot,
		DeltaTime, TankPawn->GetRotationSpeed() * 2));

	// Move to target if rotation is finished
	if (CurrentRotation.Equals(DirToMoveRot, 0.1))
	{
		//FVector NewLocation = FMath::VInterpConstantTo(TankPawn->GetActorLocation(), Location, DeltaTime, TankPawn->GetSpeed() * 2);
		TankPawn->AddActorLocalOffset(FVector::XAxisVector * DeltaTime * TankPawn->GetSpeed());
		if (TankPawn->GetActorLocation().Equals(Location, 0.1))
		{
			MoveLocation = FVector::Zero();
		}
	}
}
