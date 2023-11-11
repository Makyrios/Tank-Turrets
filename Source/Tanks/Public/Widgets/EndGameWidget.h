// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* Canvas;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DisplayText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* VerticalBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* RestartButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* RestartText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class USpacer* Spacer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainMenuButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MainMenuText;

	UPROPERTY(EditAnywhere)
	class USoundBase* OnWinSound{};
	UPROPERTY(EditAnywhere)
	class USoundBase* OnLoseSound{};
public:
	void NativeConstruct() override;
	void ChangeDisplayText(bool bPlayerWon);

	void PlaySoundDependingOnState(bool bPlayerWon);
private:
	UFUNCTION()
	void ClickRestartButton();
	UFUNCTION()
	void ClickMainMenuButton();
	
};
