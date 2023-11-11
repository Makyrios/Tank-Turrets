// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StartGameWidget.h"
#include <GameModes/BaseGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"

void UStartGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABaseGameMode* GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode != nullptr)
	{
		StartGameDelay = GameMode->StartGameDelay;
		Timer = StartGameDelay;
	}
}

void UStartGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Timer -= InDeltaTime;
	if (StartGameDelay - Timer < 1)
	{
		DisplayText->SetText(FText::FromString("Get Ready!"));
	}
	else if (FMath::CeilToInt(Timer) == 0)
	{
		DisplayText->SetText(FText::FromString("Go!"));
	}
	else if (Timer > 0)
	{
		DisplayText->SetText(FText::AsNumber(FMath::CeilToInt(Timer)));
	}
	else
	{
		RemoveFromParent();
	}
}
