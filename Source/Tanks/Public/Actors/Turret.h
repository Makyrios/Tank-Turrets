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
	
protected:
	virtual void BeginPlay() override;

	
};
