// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UHealthComponent;
class UProgressBar;

/**
 * 
 */
UCLASS()
class TANKS_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeWidget(UHealthComponent* HealthComp);

private:
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HealthBar;

	UFUNCTION()
	void OnHealthUpdate(float Value);
	
};
