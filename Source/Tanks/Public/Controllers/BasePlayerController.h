// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Actors/PawnBase.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();
	
	void RotateMuzzle(const struct FInputActionValue& Value);
	void RotateTower(const struct FInputActionValue& Value);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> DefaultMappingContext{nullptr};	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShootAction{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RotateTowerAction{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RotateMuzzleAction{nullptr};
	
	TObjectPtr<class APawnBase> PlayerChar{nullptr};

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	
	
	void Shoot(const struct FInputActionValue& Value);
	
	float LastShootTime = 0.f;
	
public:
	void SetPlayerEnabledState(bool bEnableInput);
};
