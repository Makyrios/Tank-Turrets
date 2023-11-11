// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/HealthComponent.h"

#include "GameModes/TanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UHealthComponent::DamageTaken(AActor* DamageActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("%f"), Health);

	OnHealthUpdate.Broadcast(Health);

	if (Health <= 0.f)
	{
		HandleDestroy(DamageActor);
	}
}

void UHealthComponent::HandleDestroy(AActor* DamageActor)
{
	ABaseGameMode* GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(this));
	DamageActor->Destroy();
	if (GameMode != nullptr)
	{
		GameMode->HandleActorKilled(DamageActor);
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Display, TEXT("Health comp: %s"), *GetOwner()->GetActorNameOrLabel())
	//Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}



