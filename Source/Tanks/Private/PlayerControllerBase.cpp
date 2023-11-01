// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerChar = Cast<ATank>(GetPawn());
	if (!PlayerChar) {return;}
	
	
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerControllerBase::SetupInputComponent()
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
		UEI->BindAction(ForwardMoving.Get(), ETriggerEvent::Triggered, this, &ThisClass::MoveForward);
		UEI->BindAction(SidewaysMoving.Get(), ETriggerEvent::Triggered, this, &ThisClass::MoveSideway);
		UEI->BindAction(ShootAction.Get(), ETriggerEvent::Started, this, &ThisClass::Shoot);
	}
}

void APlayerControllerBase::MoveForward(const FInputActionValue& Value)
{
	if (PlayerChar)
	{
		FVector DeltaLocation(0.f);
		DeltaLocation.X = Value.Get<float>() * GetWorld()->GetDeltaSeconds() * PlayerChar->GetSpeed();
		
		PlayerChar->AddActorLocalOffset(DeltaLocation, true);
	}
}

void APlayerControllerBase::MoveSideway(const FInputActionValue& Value)
{
	if (PlayerChar)
	{
		FRotator DeltaRotation(0.f);
		DeltaRotation.Yaw = Value.Get<float>() * GetWorld()->GetDeltaSeconds() * PlayerChar->GetRotationSpeed();
		
		PlayerChar->AddActorLocalRotation(DeltaRotation);
	}
}

void APlayerControllerBase::Shoot(const FInputActionValue& Value)
{
	if (!PlayerChar) return;

	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastShootTime >= PlayerChar->GetFireRate()) // Check if Xsec (FireRate) is passed from the last shoot
	{
		PlayerChar->Fire();
		LastShootTime = CurrentTime; // Override LastShootTime (contains last shoot time) with time when actual shoot is happening
	}
}


void APlayerControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FHitResult Result;
	GetHitResultUnderCursor(ECC_Visibility, false, Result);
	if (PlayerChar)
	{
		PlayerChar->RotateTower(Result.Location);
	}
	
}
