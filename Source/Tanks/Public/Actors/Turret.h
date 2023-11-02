// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "Turret.generated.h"


/**
 * 
 */
UCLASS()
class TANKS_API ATurret : public APawnBase
{
	GENERATED_BODY()

public:
	ATurret();
	
	void SetFireRange(float NewRange);
protected:
	
	virtual void BeginPlay() override;
private:
	
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float FireRange{ 2000.f };
};
