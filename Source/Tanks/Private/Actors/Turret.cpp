// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Turret.h"
#include "Actors/Tank.h"
#include "Kismet/GameplayStatics.h"



ATurret::ATurret()
{
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Turret"));
	
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GetWorldTimerManager().SetTimer(FireRateTimer, this, &ATurret::Fire, FireRate, true);
	
}


void ATurret::Fire()
{
	Super::Fire();
}

void ATurret::SetFireRange(float NewRange)
{
	FireRange = NewRange;
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
