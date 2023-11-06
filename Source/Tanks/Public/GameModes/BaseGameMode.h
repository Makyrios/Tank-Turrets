// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayTagContainer.h"
#include <Controllers/BasePlayerController.h>
#include "BaseGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGameStart);

/**
 * 
 */
UCLASS()
class TANKS_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	FOnGameStart OnGameStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartGameDelay = 2;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void StopGame(bool bPlayerWon);

	virtual void HandleActorKilled(AActor* KilledActor);


protected:
	void BeginPlay() override;

	virtual void HandleGameStart();
	
	TObjectPtr<ABasePlayerController> PlayerController;
	
};

