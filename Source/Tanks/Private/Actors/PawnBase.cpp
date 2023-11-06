// Fill out your copyright notice in the Description page of Project Settings.
#include "Actors/PawnBase.h"

#include "Controllers/BaseAIController.h"
#include "Actors/Projectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ActorComponents/HealthComponent.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Widgets/HealthBarWidget.h>

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
	SpringArmComponent->SetupAttachment(MeshMuzzle);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(MeshMuzzle);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar Widget Component"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetDrawSize(FVector2D(300, 20));

	HealthBarWidgetClass = LoadClass<UHealthBarWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widgets/WBP_HealthBarWidget.WBP_HealthBarWidget_C'"));
	ProjectileClass = LoadClass<AProjectile>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Actors/BP_Projectile.BP_Projectile_C'"));
}




void APawnBase::BeginPlay()
{
	Super::BeginPlay();

	
	
	InitializeController();

	InitializeHealthBar();
}

void APawnBase::InitializeController()
{
	auto AIController = Cast<ABaseAIController>(GetController());
	if (AIController != nullptr)
	{
		AIController->SetPlayer();
		AIController->SetFireRate(FireRate);
		AIController->SetFireRange(FireRange);
	}
}

void APawnBase::InitializeHealthBar()
{
	UUserWidget* Widget = CreateWidget<UHealthBarWidget>(UGameplayStatics::GetPlayerController(this, 0), HealthBarWidgetClass);
	HealthBarWidgetComponent->SetWidget(Widget);
	if (UHealthBarWidget* Health = Cast<UHealthBarWidget>(HealthBarWidgetComponent->GetWidget()))
	{
		Health->InitializeWidget(HealthComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Health widget cast fail"));
	}
}


void APawnBase::RotateTower(float LookAtTarget)
{
	FRotator TowerRotation {0.f, LookAtTarget, 0.f};
	MeshTower->AddLocalRotation(TowerRotation);
}

void APawnBase::RotateMuzzle(float LookAtTarget)
{
	FRotator MuzzleRotation {LookAtTarget, 0.f, 0.f};
	MeshMuzzle->AddLocalRotation(MuzzleRotation, true);
}

void APawnBase::RotateTowerAI(FVector LookAtTarget)
{
	FVector TagetLocation = LookAtTarget - MeshTower->GetComponentLocation();

	FRotator MeshRotation{0.f, TagetLocation.Rotation().Yaw, 0.f};
	
	MeshTower->SetWorldRotation(FMath::RInterpTo(MeshTower->GetComponentRotation(), MeshRotation,
		GetWorld()->GetDeltaSeconds(), TowerRotationSpeed));
}

void APawnBase::Fire()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform());
	Projectile->SetOwner(this);
}



