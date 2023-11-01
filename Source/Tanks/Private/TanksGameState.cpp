// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameState.h"
#include <Kismet/GameplayStatics.h>
#include "Turret.h"

void ATanksGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();

	FindAllTurrets();
}

void ATanksGameState::FindAllTurrets()
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);
	TurretAmount = Turrets.Num();
}
