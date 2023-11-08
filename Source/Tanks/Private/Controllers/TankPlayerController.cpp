// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TankPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void ATankPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerChar = Cast<ATank>(GetPawn());
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* UEI = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind the actions
		UEI->BindAction(ForwardMoving.Get(), ETriggerEvent::Triggered, this, &ATankPlayerController::MoveForward);
		UEI->BindAction(SidewaysMoving.Get(), ETriggerEvent::Triggered, this, &ATankPlayerController::MoveSideway);
		UEI->BindAction(StabilizationToggle.Get(), ETriggerEvent::Started, this, &ATankPlayerController::ToggleStabilization);
	}
}

void ATankPlayerController::MoveForward(const FInputActionValue& Value)
{
	if (!PlayerChar) return;

	FVector DeltaLocation(0.f);
	DeltaLocation.X = Value.Get<float>() * GetWorld()->GetDeltaSeconds() * PlayerChar->GetSpeed();

	PlayerChar->AddActorLocalOffset(DeltaLocation, true);
}

void ATankPlayerController::MoveSideway(const FInputActionValue& Value)
{
	if (PlayerChar)
	{
		FRotator DeltaRotation(0.f);
		DeltaRotation.Yaw = Value.Get<float>() * GetWorld()->GetDeltaSeconds() * PlayerChar->GetRotationSpeed();

		PlayerChar->AddActorLocalRotation(DeltaRotation);
		if (bIsStabilized)
		{
			FRotator NegativeDeltaRotation = DeltaRotation;
			NegativeDeltaRotation.Yaw = -NegativeDeltaRotation.Yaw;
			PlayerChar->GetMeshTower()->AddLocalRotation(NegativeDeltaRotation);
		}
	}
}

void ATankPlayerController::ToggleStabilization()
{
	bIsStabilized = !bIsStabilized;
}
