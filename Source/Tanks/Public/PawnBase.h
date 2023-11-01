// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"




UCLASS()
class TANKS_API APawnBase : public APawn
{
	GENERATED_BODY()
public:
	APawnBase();
	
	void Fire();
	void RotateTower(FVector LookAtTarget);
	
	float GetFireRate() const { return FireRate; }
	
protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshBase{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshTower{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UCapsuleComponent> CapsuleComponent{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UCameraComponent> CameraComponent{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USpringArmComponent> SpringArmComponent{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USceneComponent> ProjectileSpawnPoint{nullptr};

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float TowerRotationSpeed{10.f};
	
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float FireRate{2.f};
	FTimerHandle FireRateTimer;
	
	
	
	
	
	
	
};
