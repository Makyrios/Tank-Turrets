// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> DefaultMappingContext{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ForwardMoving{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SidewaysMoving{nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShootAction{nullptr};

	TObjectPtr<class ATank> PlayerChar{nullptr};

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void MoveForward(const struct FInputActionValue& Value);
	void MoveSideway(const struct FInputActionValue& Value);
	void Shoot(const struct FInputActionValue& Value);

	float LastShootTime = 0.f;
	
public:
	void SetPlayerEnabledState(bool bEnableInput);
};
