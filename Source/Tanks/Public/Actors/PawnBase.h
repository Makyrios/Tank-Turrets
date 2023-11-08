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

	void SetDamage(float& new_Damage);
	
	float GetRotateDegreeMax() { return RotateDegreeMax; }
	float GetRotateDegreeMin() { return RotateDegreeMin; }	
	
	inline float GetFireRate() const { return FireRate; }
	inline float GetFireRange() const { return FireRange; }
	inline float GetTowerRotationSpeed() const { return TowerRotationSpeed; }

	inline void SetFireRange(float NewFireRange) { FireRange = NewFireRange; }
	inline void SetFireRate(float NewFireRate) { FireRate = NewFireRate; }
	inline void SetTowerRotationSpeed(float NewRotationSpeed) { TowerRotationSpeed = NewRotationSpeed; }
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void UpdateHealthBarVisibility();

	void InitializeHealthBar();

	void InitializeController();

	bool MuzzleRotationInRange(const float& LookAtTarget);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshBase{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshTower{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshMuzzle{nullptr};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCameraComponent> CameraComponent{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USpringArmComponent> SpringArmComponent{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USceneComponent> ProjectileSpawnPoint{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UHealthComponent> HealthComponent{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UWidgetComponent> HealthBarWidgetComponent{nullptr};

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UHealthBarWidget> HealthBarWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float TowerRotationSpeed{10.f};

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float MuzzleRotationSpeed{ 10.f };
	
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float FireRate{2.f};

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float FireRange{ 2000.f };
	
	FTimerHandle FireRateTimer;
	
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float RotateDegreeMin{-12.0f};
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float RotateDegreeMax{15.0f};

	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = true))
	float HealthBarVisibilityRange{ 500.f };

private:
	TObjectPtr<APawn> PlayerPawn;
	float Damage{ 10.f };
};
