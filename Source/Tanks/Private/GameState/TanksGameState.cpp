// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/TanksGameState.h"
#include <Kismet/GameplayStatics.h>
#include "Actors/Turret.h"


int ATanksGameState::FindAllEnemies() const
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsWithTag(this, FName("Turret"), Turrets);
	return Turrets.Num();
}
