// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	
	UFUNCTION()
	void DamageTaken(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);

	void HandleDestroy(AActor* DamageActor);
	
	float GetHealth() const { return Health; }
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere,Category = "Health" , meta = (AllowPrivateAccess = true))
	float MaxHealth = 100.f;
	float Health = 0.f;
};
