// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TankAIController.h"
#include "NavigationSystem.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>

void ATankAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TankPawn = Cast<ATank>(InPawn);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void ATankAIController::ExecuteTasks(float DeltaTime)
{
	Super::ExecuteTasks(DeltaTime);

	if (PlayerPawn == nullptr || TankPawn == nullptr) { return; }

	RotateBaseToMovement();
	SetRandomMoveLocation(DeltaTime);
}

void ATankAIController::SetRandomMoveLocation(float DeltaTime)
{
	FVector CurrentLocation = TankPawn->GetActorLocation();
	// If MoveToLocation is empty set new point and start moving to it
	if (MoveLocation.IsZero() || FVector::PointsAreNear(CurrentLocation, MoveLocation, 300))
	{
		// Set new point
		FindMoveToLocation(PlayerPawn->GetActorLocation(), 1500);
		// Move to point
		MoveToLocation(MoveLocation, 1);
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MoveLocation);
	}
}

void ATankAIController::FindMoveToLocation(const FVector& Point, float Radius)
{
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, Point, MoveLocation, Radius);
}

void ATankAIController::RotateBaseToMovement()
{
	TankPawn->RotateBase(TankPawn->GetVelocity().Rotation());
}

//void ATankAIController::MoveToLocation(const FVector& Location, float DeltaTime)
//{
//	// Rotate to
//	FRotator DirToMoveRot = (Location - TankPawn->GetActorLocation()).Rotation();
//	FRotator CurrentRotation = TankPawn->GetActorRotation();
//	TankPawn->SetActorRotation(FMath::RInterpConstantTo(CurrentRotation, DirToMoveRot,
//		DeltaTime, TankPawn->GetRotationSpeed() * 2));
//
//	// Move to target if rotation is finished
//	if (CurrentRotation.Equals(DirToMoveRot, 0.1))
//	{
//		//FVector NewLocation = FMath::VInterpConstantTo(TankPawn->GetActorLocation(), Location, DeltaTime, TankPawn->GetSpeed() * 2);
//		TankPawn->AddActorLocalOffset(FVector::XAxisVector * DeltaTime * TankPawn->GetSpeed());
//		if (TankPawn->GetActorLocation().Equals(Location, 0.1))
//		{
//			MoveLocation = FVector::Zero();
//		}
//	}
//}
