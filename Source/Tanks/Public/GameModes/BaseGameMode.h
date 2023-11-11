// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayTagContainer.h"
#include <Controllers/BasePlayerController.h>
#include "BaseGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGameStart);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameEnd, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyKilled);

/**
 * 
 */
UCLASS()
class TANKS_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseGameMode();

	FOnGameStart OnGameStart;
	FOnGameEnd OnGameEnd;
	UPROPERTY(BlueprintAssignable)
	FOnEnemyKilled OnEnemyKilled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rules)
	float StartGameDelay = 2;

	virtual void HandleActorKilled(AActor* KilledActor);


protected:
	void BeginPlay() override;

	virtual void HandleGameStart();
	
	TObjectPtr<ABasePlayerController> PlayerController;
	
};

