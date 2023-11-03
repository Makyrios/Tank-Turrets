// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthUpdate, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION()
	void DamageTaken(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);

	void HandleDestroy(AActor* DamageActor);
	
	inline float GetHealth() const { return Health; }
	inline float GetMaxHealth() const { return MaxHealth; }
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FOnHealthUpdate OnHealthUpdate;

private:
	UPROPERTY(EditAnywhere, Category = "Health", meta = (AllowPrivateAccess = true))
	float MaxHealth = 100.f;
	float Health = 0.f;
};
