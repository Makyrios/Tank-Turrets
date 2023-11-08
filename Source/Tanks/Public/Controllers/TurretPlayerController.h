// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/BasePlayerController.h"
#include "TurretPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATurretPlayerController : public ABasePlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Input)
	float RotationSpeed = 0.5f;
	
};
