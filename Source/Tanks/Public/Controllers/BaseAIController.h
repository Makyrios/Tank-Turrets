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
	//virtual void SetFireRate(float newFireRate);
	//virtual void SetFireRange(float newFireRange);
	float GetFireRange() const;
	float GetFireRate() const;

	void SetControlEnabledState(bool bEnableInput);

private:
	float FireRate{ 2.f };
	float FireRange;
	float LastShootTime{ 0.f };
	
	bool bEnableControl = false;

protected:
	TObjectPtr<class APawnBase> PlayerPawn{ nullptr };
	TObjectPtr<class APawnBase>	PPawn{ nullptr };
	FVector CurrentPosition{ 0.0f };

	virtual void ExecuteTasks();

	virtual void Tick(float DeltaSeconds) override final;
	void ShootInFireRange();
	void RotateTurretToPlayer();
	virtual bool InFireRange();
	virtual void OnPossess(APawn* InPawn) override;

private:
	void OnGameStart();

};
