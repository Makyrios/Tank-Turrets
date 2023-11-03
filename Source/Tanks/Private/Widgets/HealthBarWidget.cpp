// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HealthBarWidget.h"
#include <Components/ProgressBar.h>
#include "ActorComponents/HealthComponent.h"

void UHealthBarWidget::InitializeWidget(UHealthComponent* HealthComp)
{
	if (HealthComp != nullptr)
	{
		HealthComp->OnHealthUpdate.AddUObject(this, &UHealthBarWidget::OnHealthUpdate);
		HealthComponent = HealthComp;
		OnHealthUpdate(HealthComponent->GetHealth());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget is not initialized. HealthComponent is null"));
	}
}

void UHealthBarWidget::OnHealthUpdate(float Value)
{
	if (HealthComponent == nullptr || HealthBar == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("%s health is updated: %f"), *HealthComponent->GetOwner()->GetActorNameOrLabel(), Value);
	HealthBar->SetPercent(Value / HealthComponent->GetMaxHealth());
}
