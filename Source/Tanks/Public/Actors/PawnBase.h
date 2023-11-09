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
	
	virtual void Fire();
	void RotateTower(float LookAtTarget);
	void RotateMuzzle(float LookAtTarget);
	
	void RotateTowerAI(FVector LookAtTarget);
	void RotateMuzzleAI(FRotator LookAtTarget);
	
	
	FORCEINLINE float GetRotateDegreeMax() const { return RotateDegreeMax; }
	FORCEINLINE float GetRotateDegreeMin() const { return RotateDegreeMin; }	
	
	FORCEINLINE float GetFireRate() const { return FireRate; }
	FORCEINLINE float GetFireRange() const { return FireRange; }
	FORCEINLINE float GetTowerRotationSpeed() const { return TowerRotationSpeed; }
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetMeshTower() const { return MeshTower; }
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetBaseMesh() const { return MeshBase; }
	
	FORCEINLINE void SetFireRange(float NewFireRange) { FireRange = NewFireRange; }
	FORCEINLINE void SetFireRate(float NewFireRate) { FireRate = NewFireRate; }
	FORCEINLINE void SetTowerRotationSpeed(float NewRotationSpeed) { TowerRotationSpeed = NewRotationSpeed; }
	FORCEINLINE void SetDamage(float NewDamage) { Damage = NewDamage; }
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	void UpdateHealthBarVisibility();

	void InitializeHealthBar();
	
	void InitializeController();

	bool MuzzleRotationInRange(const float& LookAtTarget);

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SceneComponent{nullptr};
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshBase{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshTower{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshMuzzle{nullptr};
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UCameraComponent> CameraComponent{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USpringArmComponent> SpringArmComponent{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USceneComponent> ProjectileSpawnPoint{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UHealthComponent> HealthComponent{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UWidgetComponent> HealthBarWidgetComponent{nullptr};

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UHealthBarWidget> HealthBarWidgetClass;
	
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float TowerRotationSpeed{10.f};

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MuzzleRotationSpeed{ 10.f };
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate{2.f};
	FTimerHandle FireRateTimer;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange{ 2000.f };

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage{ 10.f };
	
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float RotateDegreeMin{-12.0f};
	UPROPERTY(EditAnywhere, Category = "Combat")
	float RotateDegreeMax{15.0f};

	UPROPERTY(EditAnywhere, Category = "UI")
	float HealthBarVisibilityRange{ 1500.f };

	
	bool bIsPlayer = false;

private:
	TObjectPtr<APawn> PlayerPawn;
	
};
