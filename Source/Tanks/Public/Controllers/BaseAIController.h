// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void SetPlayer();
	virtual void SetFireRate(float newFireRate);
	virtual void SetFireRange(float newFireRange);
private:
	float FireRate{ 0.f };
	float FireRange{ 300.f };
	float LastShootTime{ 0.f };

protected:
	TObjectPtr<class APawnBase> PlayerPawn{ nullptr };
	TObjectPtr<class APawnBase>	PPawn{ nullptr };
	FVector CurPosition{ 0.0f };

	virtual void Tick(float DeltaSeconds) override;
	virtual bool InFireRange();
	virtual void OnPossess(APawn* InPawn) override;
};
