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
#include "Kismet/KismetMathLibrary.h"

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
	HealthBarWidgetComponent->SetupAttachment(MeshBase);
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetDrawSize(FVector2D(250, 20));

	
	HealthBarWidgetClass = LoadClass<UHealthBarWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widgets/Game/WBP_HealthBarWidget.WBP_HealthBarWidget_C'"));
	ProjectileClass = LoadClass<AProjectile>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Actors/BP_Projectile.BP_Projectile_C'"));
}




void APawnBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (PlayerPawn == this)
	{
		bIsPlayer = true;
	}

	if (!bIsPlayer)
	{
		InitializeHealthBar();
	}	
}

void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsPlayer)
	{
		UpdateHealthBarVisibility();
	}
}

bool APawnBase::InHealthBarVisibilityRange()
{	
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector Start = MeshTower->GetComponentLocation();
	FVector End = Start + (PlayerPawn->GetActorLocation() - Start).GetSafeNormal() * HealthBarVisibilityRange;

	bool bWasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params);
	if (bWasHit)
	{
		if (HitResult.GetActor()->ActorHasTag(FName("Player")))
		{
			return true;
		}
	}
	return false;
}

float APawnBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	ShowHealthBarOnDamageTaken();
	return 0.0f;
}

void APawnBase::ShowHealthBarOnDamageTaken()
{
	LastTimeDamageTaken = GetWorld()->GetTimeSeconds();
	HealthBarWidgetComponent->SetVisibility(true);
	TakenDamageRecently = true;
}

void APawnBase::UpdateHealthBarVisibility()
{		
	if (TakenDamageRecently)
	{	
		float CurrentTime = GetWorld()->GetTimeSeconds();
		if (CurrentTime - LastTimeDamageTaken >= TimeToShowHealthOnDamage)
		{
			TakenDamageRecently = false;
		}

		return;
	}

	if (InHealthBarVisibilityRange())
	{
		HealthBarWidgetComponent->SetVisibility(true);
		return;
	}
	HealthBarWidgetComponent->SetVisibility(false);
}

void APawnBase::InitializeController()
{
	/*auto AIController = Cast<ABaseAIController>(GetController());
	if (AIController != nullptr)
	{
		AIController->SetPlayer();
		AIController->SetFireRange(FireRange);
		AIController->SetFireRate(FireRate);
	}*/
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

bool APawnBase::MuzzleRotationInRange(const float& LookAtTarget)
{	
	double CurrentRotation = MeshMuzzle->GetRelativeRotation().Pitch;
	if ((CurrentRotation >= RotateDegreeMin && LookAtTarget < 0.f) ||
		(CurrentRotation <= RotateDegreeMax && LookAtTarget > 0.f))
	{
		return true;
	}
	return false;
}


void APawnBase::RotateTower(float LookAtTarget)
{
	FRotator TowerRotation {0.f, LookAtTarget, 0.f};
	MeshTower->AddLocalRotation(TowerRotation);
}

void APawnBase::RotateMuzzle(float LookAtTarget)
{
	FRotator MuzzleRotation {LookAtTarget, 0.f, 0.f};
	if (MuzzleRotationInRange(LookAtTarget))
	{
		MeshMuzzle->AddLocalRotation(MuzzleRotation, true);
	}
	
}

void APawnBase::RotateTowerAI(FVector LookAtTarget)
{
	FVector TargetLocation = LookAtTarget - MeshTower->GetComponentLocation();

	FRotator MeshRotation{0.f, TargetLocation.Rotation().Yaw, 0.f};
	
	MeshTower->SetWorldRotation(FMath::RInterpTo(MeshTower->GetComponentRotation(), MeshRotation,
		GetWorld()->GetDeltaSeconds(), TowerRotationSpeed));
}

void APawnBase::RotateMuzzleAI(FRotator LookAtTarget)
{	
	double deltaAngle = LookAtTarget.Pitch - MeshMuzzle->GetRelativeRotation().Pitch;
	if (MuzzleRotationInRange(deltaAngle))
	{
		MeshMuzzle->AddRelativeRotation({ deltaAngle,0,0 });
	}	
}

void APawnBase::SetDamage(float& NewDamage)
{
	Damage = NewDamage;
}


void APawnBase::Fire()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform());
	if (Projectile)
	{
		Projectile->SetOwner(this);
		Projectile->SetDamage(Damage);
	}
	
	
}



