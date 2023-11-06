// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TurretPlayerController.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"

void ATurretPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* UEI = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind the actions
		UEI->BindAction(RotateCameraAction.Get(), ETriggerEvent::Triggered, this, &ATurretPlayerController::RotateCamera);
	}
}

void ATurretPlayerController::RotateCamera(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X * RotationSpeed);
}
