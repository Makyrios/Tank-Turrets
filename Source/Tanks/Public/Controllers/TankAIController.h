// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/BaseAIController.h"
#include <Actors/Tank.h>
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankAIController : public ABaseAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void ExecuteTasks(float DeltaTime) override;

private:
	TObjectPtr<ATank> TankPawn;
	TObjectPtr<APawn> PlayerPawn;

	FVector MoveLocation;

	void SetRandomMoveLocation(float DeltaTime);

	void FindMoveToLocation(const FVector& Point, float Radius);

	void RotateBaseToMovement();

	//void MoveToLocation(const FVector& Location, float DeltaTime);

};
