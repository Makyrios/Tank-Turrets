// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"

#include "Actors/PawnBase.h"
#include "Kismet/GameplayStatics.h"

void ABaseAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (PlayerPawn != nullptr && PPawn != nullptr)
	{
		PPawn->RotateTower(PlayerPawn->GetActorLocation());
	}
	if (InFireRange())
	{	
		float CurrentTime = GetWorld()->GetTimeSeconds();
		if (CurrentTime - LastShootTime >= FireRate) // Check if Xsec (FireRate) is passed from the last shoot
		{
			PPawn->Fire();
			LastShootTime = CurrentTime; // Override LastShootTime (contains last shoot time) with time when actual shoot is happening
		}
	}
}

bool ABaseAIController::InFireRange()
{
	if (PlayerPawn != nullptr && PPawn != nullptr)
	{
		float Dist = FVector::Dist(CurPosition, PlayerPawn->GetActorLocation());
		if (Dist <= FireRange)
		{
			return true;
		}
	}
	return false;
}

void ABaseAIController::SetPlayer()
{
	PlayerPawn = Cast<APawnBase>(UGameplayStatics::GetPlayerPawn(this, 0));	
}

void ABaseAIController::SetFireRate(float newFireRate)
{
	FireRate = newFireRate;
}

void ABaseAIController::SetFireRange(float newFireRange)
{
	FireRange = newFireRange;
}

void ABaseAIController::OnPossess(APawn* InPawn)
{	
	Super::OnPossess(InPawn);
	PPawn = Cast<APawnBase>(InPawn);
	CurPosition = PPawn->GetActorLocation();
}

