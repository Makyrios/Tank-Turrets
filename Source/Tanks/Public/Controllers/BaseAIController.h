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
	
	float GetFireRange() const { return FireRange; }
	float GetFireRate() const { return FireRate; }

	void SetControlEnabledState(bool bEnableInput);
protected:
	
	TObjectPtr<class APawnBase> PlayerPawn{ nullptr };
	TObjectPtr<class APawnBase>	PPawn{ nullptr };
	FVector CurrentPosition{ 0.0f };

	virtual void ExecuteTasks(float DeltaTime);

	virtual void Tick(float DeltaSeconds) override final;
	void ShootInFireRange();
	void RotateTurretToPlayer();
	void RotateMuzzleToPlayer();
	virtual bool InFireRange();
	virtual void OnPossess(APawn* InPawn) override;

private:
	void OnGameStart();
	
	float FireRate{ 2.f };
	float FireRange;
	float LastShootTime{ 0.f };
	
	bool bEnableControl = false;
};
