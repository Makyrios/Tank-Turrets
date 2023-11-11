// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <GameModes/BaseGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"
#include "Widgets/StartGameWidget.h"
#include "Widgets/EndGameWidget.h"


ABasePlayerController::ABasePlayerController()
{
	HUDWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widgets/HUD/WBP_HUD.WBP_HUD_C'"));
	StartGameWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widgets/Game/WBP_StartGameWidget.WBP_StartGameWidget_C'"));
	EndGameWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widgets/Game/WBP_EndGameWidget.WBP_EndGameWidget_C'"));
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	ABaseGameMode* GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(this));
	GameMode->OnGameStart.AddUObject(this, &ABasePlayerController::OnGameStart);
	GameMode->OnGameEnd.AddUObject(this, &ABasePlayerController::OnGameEnd);
}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerChar = Cast<APawnBase>(InPawn);
	if (PlayerChar != nullptr)
	{
		PlayerChar->Tags.Add(FName("Player"));
	}
	
	if (OnPossesPlayerSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), OnPossesPlayerSound);
	}
	
	InitializeControls();
	InitializeWidgets();
}

void ABasePlayerController::InitializeControls()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	SetControlEnabledState(false);
}

void ABasePlayerController::InitializeWidgets()
{
	if (HUDWidgetClass != nullptr)
	{
		HUD = CreateWidget(this, HUDWidgetClass);
	}
	if (StartGameWidgetClass != nullptr)
	{
		StartGameWidget = CreateWidget<UStartGameWidget>(this, StartGameWidgetClass);
		StartGameWidget->AddToViewport();
	}
	if (EndGameWidgetClass != nullptr)
	{
		EndGameWidget = CreateWidget<UEndGameWidget>(this, EndGameWidgetClass);
	}
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
		UEI->BindAction(RotateTowerAction.Get(), ETriggerEvent::Triggered, this, &ABasePlayerController::RotateTower);
		UEI->BindAction(RotateMuzzleAction.Get(), ETriggerEvent::Triggered, this, &ABasePlayerController::RotateMuzzle);
	}
}

void ABasePlayerController::Shoot(const FInputActionValue& Value)
{
	if (!PlayerChar) return;

	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastShootTime >= PlayerChar->GetFireRate()) // Check if Xsec (FireRate) is passed from the last shoot
	{
		PlayerChar->Fire();
		LastShootTime = CurrentTime; 
	}
}

void ABasePlayerController::SetControlEnabledState(bool bEnableInput)
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

void ABasePlayerController::OnGameStart()
{
	SetControlEnabledState(true);
	HUD->AddToViewport();
}

void ABasePlayerController::OnGameEnd(bool bPlayerWon)
{
	SetControlEnabledState(false);
	HUD->RemoveFromParent();
	if (EndGameWidget != nullptr)
	{
		EndGameWidget->ChangeDisplayText(bPlayerWon);
		EndGameWidget->AddToViewport();
	}
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABasePlayerController::RotateMuzzle(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	if (PlayerChar)
	{
		PlayerChar->AddControllerPitchInput(AxisValue);
		PlayerChar->RotateMuzzle(AxisValue);
	}
}

void ABasePlayerController::RotateTower(const struct FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	if (PlayerChar)
	{
		PlayerChar->AddControllerYawInput(AxisValue);
		PlayerChar->RotateTower(AxisValue);
	}
}
