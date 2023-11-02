// Fill out your copyright notice in the Description page of Project Settings.
#include "Actors/PawnBase.h"

#include "Controllers/BaseAIController.h"
#include "Actors/Projectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Base"));
	RootComponent = MeshBase;
	
	MeshTower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Tower"));
	MeshTower->SetupAttachment(MeshBase);

	MeshMuzzle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Muzzle"));
	MeshMuzzle->SetupAttachment(MeshTower);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(MeshMuzzle);
}


void APawnBase::RotateTower(FVector LookAtTarget)
{
	FVector TargetLocation = LookAtTarget - MeshTower->GetComponentLocation();
	FRotator MeshRotation{0.f, TargetLocation.Rotation().Yaw, 0.f};

	MeshTower->SetWorldRotation(FMath::RInterpTo(MeshTower->GetComponentRotation(), MeshRotation,
		GetWorld()->GetDeltaSeconds(), TowerRotationSpeed));
}

void APawnBase::BeginPlay()
{
	auto AIController = Cast<ABaseAIController>(GetController());
	if (AIController != nullptr)
	{
		AIController->SetPlayer();
		AIController->SetFireRate(FireRate);
		AIController->SetFireRange(FireRange);
	}
}


void APawnBase::Fire()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform());
}





