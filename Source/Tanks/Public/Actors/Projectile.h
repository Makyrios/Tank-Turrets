// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void SetDamage(float& NewDamage);
	
protected:
	virtual void BeginPlay() override;

	void DeleteProjectileAfterSpawn();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComponent{nullptr};
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh{nullptr};
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileDamage{10.f};

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileLifeTime{ 5.f };

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<class UParticleSystem> OnHitParticle {nullptr};
	
	UPROPERTY(EditAnywhere, Category = "Sounds")
	TObjectPtr<class UAudioComponent> AudioComponent {nullptr};
	
	UPROPERTY(EditAnywhere, Category = "Sounds")
	TObjectPtr<class USoundBase> OnHitSound {nullptr};

	UPROPERTY(EditAnywhere, Category = "Sounds")
	TObjectPtr<class USoundBase> StartFireSound {nullptr};
	
};
