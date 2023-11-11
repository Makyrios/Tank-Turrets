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

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundBase> OnPossesPlayerSound{nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UStartGameWidget> StartGameWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UEndGameWidget> EndGameWidgetClass;
	
	TObjectPtr<class APawnBase> PlayerChar{nullptr};

	float LastShootTime = 0.f;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	void InitializeControls();
	void InitializeWidgets();
	
	
	void Shoot(const struct FInputActionValue& Value);
	
	void OnGameStart();
	void OnGameEnd(bool bPlayerWon);
	
public:
	void SetControlEnabledState(bool bEnableInput);

private:
	UUserWidget* HUD;
	UPROPERTY()
	UStartGameWidget* StartGameWidget;
	UPROPERTY()
	UEndGameWidget* EndGameWidget;
};
