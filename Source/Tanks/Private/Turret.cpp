// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"


#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"



void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GetWorldTimerManager().SetTimer(FireRateTimer, this, &ATurret::Fire, FireRate, true);
	
}

void ATurret::Fire()
{
	Super::Fire();
}

void ATurret::SetFireRange(float newRange)
{
	FireRange = newRange;
}

void ATurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (InFireRange())
	{
		RotateTower(PlayerTank->GetActorLocation());
	}
}

bool ATurret::InFireRange()
{
	if (PlayerTank)
	{
		float Dist = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());
		if (Dist <= FireRange)
		{
			return true;
		}
	}
	return false;
}
