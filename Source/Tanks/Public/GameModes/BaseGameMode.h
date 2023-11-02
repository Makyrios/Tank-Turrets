// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayTagContainer.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartGameDelay = 2;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void StopGame(bool bPlayerWon);

	virtual void HandleActorKilled(AActor* KilledActor);


protected:
	virtual void HandleGameStart();
	
};

