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

protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
private:

	TObjectPtr<class ATank> PlayerTank{nullptr};
	
	UPROPERTY(EditAnywhere, Category = Combat, meta = (AllowPrivateAccess = true))
	float FireRange{ 200.f };

	void AssessFireCondition();
	
	bool InFireRange();
};
