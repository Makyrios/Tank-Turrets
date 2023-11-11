// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"

#include "Actors/PawnBase.h"
#include "Kismet/GameplayStatics.h"
#include <GameModes/BaseGameMode.h>
#include "Kismet/KismetMathLibrary.h"

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PPawn = Cast<APawnBase>(InPawn);
	PlayerPawn = Cast<APawnBase>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (PlayerPawn != nullptr)
	{
		SetControlEnabledState(false);
		ABaseGameMode* GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(this));
		GameMode->OnGameStart.AddUObject(this, &ABaseAIController::OnGameStart);
	}
}

void ABaseAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerPawn == nullptr || PPawn == nullptr) { return; }

	if (bEnableControl)
	{
		ExecuteTasks(DeltaSeconds);
	}

}

void ABaseAIController::ExecuteTasks(float DeltaTime)
{	
	if (PlayerPawn != nullptr && PPawn != nullptr)
	{			
		RotateTurretToPlayer();
		RotateMuzzleToPlayer();
		ShootInFireRange();
	}
	
}

void ABaseAIController::ShootInFireRange()
{
	if (InFireRange())
	{
		float CurrentTime = GetWorld()->GetTimeSeconds();
		if (CurrentTime - LastShootTime >= PPawn->GetFireRate()) // Check if Xsec (FireRate) is passed from the last shoot
		{
			PPawn->Fire();
			LastShootTime = CurrentTime; // Override LastShootTime (contains last shoot time) with time when actual shoot is happening
		}
	}
}

void ABaseAIController::RotateTurretToPlayer()
{
	PPawn->RotateTowerAI(PlayerPawn->GetActorLocation());
}

void ABaseAIController::RotateMuzzleToPlayer()
{	
	FRotator LookAtPlayer = UKismetMathLibrary::FindLookAtRotation(PPawn->GetMeshTower()->GetComponentLocation(), PlayerPawn->GetBaseMesh()->GetComponentLocation());
	PPawn->RotateMuzzleAI(LookAtPlayer);
}

void ABaseAIController::OnGameStart()
{
	SetControlEnabledState(true);
}

bool ABaseAIController::InFireRange()
{
	if (PlayerPawn != nullptr && PPawn != nullptr)
	{
		float Dist = FVector::Dist(PPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
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


