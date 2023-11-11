// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/TurretGameState.h"
#include "Actors/Tank.h"
#include <Kismet/GameplayStatics.h>



int ATurretGameState::FindAllEnemies() const
{
	TArray<AActor*> Tanks;
	UGameplayStatics::GetAllActorsOfClass(this, ATank::StaticClass(), Tanks);
	return Tanks.Num();
}
