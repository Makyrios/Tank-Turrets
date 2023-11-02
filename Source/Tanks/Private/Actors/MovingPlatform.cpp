// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MovingPlatform.h"
#include "Engine/TargetPoint.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void AMovingPlatform::Initialize()
{
	SetNullPoints();

	MoveDirectionUnitVector = (EndPoint->GetActorLocation() - StartPoint->GetActorLocation()).GetSafeNormal();
	StartLocation = GetActorLocation();
	MoveDistance = (EndPoint->GetActorLocation() - StartPoint->GetActorLocation()).Size();

	SetActorRotation(MoveDirectionUnitVector.Rotation());
}

void AMovingPlatform::SetNullPoints()
{
	if (EndPoint == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("End point is not set for %s"), *GetActorNameOrLabel());
		EndPoint = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass(),
			GetActorLocation() + GetActorForwardVector() * MoveDistanceWithoutEndPoint, FRotator::ZeroRotator);
	}
	if (StartPoint == nullptr)
	{
		StartPoint = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	CheckIfReachTargetPoint();
}


void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += MoveDirectionUnitVector * MovementSpeed * DeltaTime;
	CurrentMoveDistance += (CurrentLocation - GetActorLocation()).Size();
	SetActorLocation(CurrentLocation);
}

void AMovingPlatform::CheckIfReachTargetPoint()
{
	if (ReachedEndPoint())
	{
		CurrentMoveDistance = 0;
		if (ShouldPlatformReturn())
		{
			MoveDirectionUnitVector *= -1;
			NumOfReturns -= 1;
		}
		else
		{
			Destroy();
		}
	}
}


bool AMovingPlatform::ReachedEndPoint() const
{
	return CurrentMoveDistance >= MoveDistance;
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	if (!bShouldReturn || NumOfReturns == 0)
	{
		return false;
	}
	if (NumOfReturns < 0)
	{
		return true;
	}

	return true;
}
