// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"

#include "Actors/PawnBase.h"
#include "Kismet/GameplayStatics.h"

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	PPawn = Cast<APawnBase>(InPawn);
	PlayerPawn = Cast<APawnBase>(UGameplayStatics::GetPlayerPawn(this, 0));
	CurrentPosition = PPawn->GetActorLocation();
}

void ABaseAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bEnableControl)
	{
		RotateToPlayer();
		ShootInFireRange();
	}

}

void ABaseAIController::ShootInFireRange()
{
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

void ABaseAIController::RotateToPlayer()
{
	if (PlayerPawn != nullptr && PPawn != nullptr)
	{
		PPawn->RotateTower(PlayerPawn->GetActorLocation());
	}
}

bool ABaseAIController::InFireRange()
{
	if (PlayerPawn != nullptr && PPawn != nullptr)
	{
		float Dist = FVector::Dist(CurrentPosition, PlayerPawn->GetActorLocation());
		float Range = GetFireRange();
		if (Dist <= Range)
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

//void ABaseAIController::SetFireRate(float newFireRate)
//{
//	FireRate = newFireRate;
//}
//
//void ABaseAIController::SetFireRange(float newFireRange)
//{
//	FireRange = newFireRange;
//}

float ABaseAIController::GetFireRange() const
{
	return PPawn->GetFireRange();
}

float ABaseAIController::GetFireRate() const
{
	return PPawn->GetFireRate();
}

void ABaseAIController::SetControlEnabledState(bool bEnableInput)
{
	bEnableControl = bEnableInput;
}


