// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATank : public APawnBase
{
	GENERATED_BODY()

public:
	ATank();

	float GetSpeed() { return MovingSpeed; }
	float GetRotationSpeed() { return RotationSpeed; }
	
	void SetMovingSpeed(float NewMovingSpeed) { MovingSpeed = NewMovingSpeed; }
	void SetRotationSpeed(float NewRotationSpeed) { RotationSpeed = NewRotationSpeed; }

protected:
	void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float MovingSpeed {20.f};

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float RotationSpeed {20.f};


};
