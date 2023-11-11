// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile.h"

#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;

	OnHitParticle = CreateDefaultSubobject<UParticleSystem>(TEXT("OnHit Particle"));
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComponent);
	
	
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	if (StartFireSound)
	{
		AudioComponent->Sound = StartFireSound;
		AudioComponent->Play();
		
		AudioComponent->Sound = nullptr;
	}
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::DeleteProjectileAfterSpawn, ProjectileLifeTime, false);
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void AProjectile::DeleteProjectileAfterSpawn()
{
	if (this)
	{
		Destroy();
	}
}

void AProjectile::SetDamage(float& NewDamage)
{
	ProjectileDamage = NewDamage;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& HitResult)
{
	
	
	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, GetInstigatorController(), this, UDamageType::StaticClass());
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnHitParticle, GetActorLocation());

		if (OnHitSound)
		{
			AudioComponent->Sound = OnHitSound;
			AudioComponent->Play();
			
			AudioComponent->Sound = nullptr;
		}
	}
	
	Destroy();
}


