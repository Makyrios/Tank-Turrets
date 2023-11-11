// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/EndGameWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>


void UEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RestartButton->OnClicked.AddDynamic(this, &UEndGameWidget::ClickRestartButton);
	MainMenuButton->OnClicked.AddDynamic(this, &UEndGameWidget::ClickMainMenuButton);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController != nullptr)
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
	}
}

void UEndGameWidget::ChangeDisplayText(bool bPlayerWon)
{
	if (DisplayText == nullptr) return;

	if (bPlayerWon)
	{
		DisplayText->SetText(FText::FromString("You won!"));
	}
	else
	{
		DisplayText->SetText(FText::FromString("You lost!"));
	}
	PlaySoundDependingOnState(bPlayerWon);
}

void UEndGameWidget::PlaySoundDependingOnState(bool bPlayerWon)
{
	if (bPlayerWon)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), OnWinSound);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), OnLoseSound);
	}
}

void UEndGameWidget::ClickRestartButton()
{
	FString LevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(LevelName));
}

void UEndGameWidget::ClickMainMenuButton()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}
