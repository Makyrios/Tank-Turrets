// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/BaseAIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankAIController : public ABaseAIController
{
	GENERATED_BODY()
	
protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
};
