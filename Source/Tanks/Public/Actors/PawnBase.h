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

	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void Fire();
	void RotateTower(float LookAtTarget);
	void RotateMuzzle(float LookAtTarget);
	
	void RotateTowerAI(FVector LookAtTarget);
	void RotateMuzzleAI(FRotator LookAtTarget);

	void SetDamage(float& NewDamage);
	
	inline float GetRotateDegreeMax() const { return RotateDegreeMax; }
	inline float GetRotateDegreeMin() const { return RotateDegreeMin; }	
	
	inline float GetFireRate() const { return FireRate; }
	inline float GetFireRange() const { return FireRange; }
	inline float GetTowerRotationSpeed() const { return TowerRotationSpeed; }
	inline TObjectPtr<UStaticMeshComponent> GetMeshTower() const { return MeshTower; }
	inline TObjectPtr<UStaticMeshComponent> GetBaseMesh() const { return MeshBase; }
	
	inline void SetFireRange(const float NewFireRange) { FireRange = NewFireRange; }
	inline void SetFireRate(const float NewFireRate) { FireRate = NewFireRate; }
	inline void SetTowerRotationSpeed(const float NewRotationSpeed) { TowerRotationSpeed = NewRotationSpeed; }
	inline void SetHealthBarVisibilityRange(const float NewRange) { HealthBarVisibilityRange = NewRange; }

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	bool InHealthBarVisibilityRange();

	void ShowHealthBarOnDamageTaken();

	void UpdateHealthBarVisibility();

	void InitializeHealthBar();

	void InitializeController();

	bool MuzzleRotationInRange(const float& LookAtTarget);

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent{nullptr};
	
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

	UPROPERTY(EditAnywhere, Category = "HUD")
	float TimeToShowHealthOnDamage{ 3.f };
	float LastTimeDamageTaken{ 0.f };
	
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float TowerRotationSpeed{10.f};

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float MuzzleRotationSpeed{ 10.f };
	
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float FireRate{2.f};

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float FireRange{ 2000.f };

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float Damage{ 10.f };

	
	FTimerHandle FireRateTimer;
	
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float RotateDegreeMin{-12.0f};
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float RotateDegreeMax{15.0f};

	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = true))
	float HealthBarVisibilityRange{ 1500.f };

	
	bool bIsPlayer = false;

private:
	TObjectPtr<APawn> PlayerPawn;

	bool TakenDamageRecently = false;
};
