// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerChar = Cast<APawnBase>(GetPawn());
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Clear out existing mapping, and add our mapping
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Get the EnhancedInputComponent
	if (UEnhancedInputComponent* UEI = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind the actions
		UEI->BindAction(ShootAction.Get(), ETriggerEvent::Started, this, &ABasePlayerController::Shoot);
	}
}

void ABasePlayerController::Shoot(const FInputActionValue& Value)
{
	if (!PlayerChar) return;

	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastShootTime >= PlayerChar->GetFireRate()) // Check if Xsec (FireRate) is passed from the last shoot
	{
		PlayerChar->Fire();
		LastShootTime = CurrentTime; // Override LastShootTime (contains last shoot time) with time when actual shoot is happening
	}
}

void ABasePlayerController::SetPlayerEnabledState(bool bEnableInput)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (bEnableInput)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		else
		{
			Subsystem->ClearAllMappings();
		}
	}
}


void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FHitResult Result;
	GetHitResultUnderCursor(ECC_Visibility, false, Result);
	if (PlayerChar)
	{
		PlayerChar->RotateTower(Result.Location);
	}
	
}
