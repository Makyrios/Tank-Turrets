// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* StaticMesh;

	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Initialize();

	void MovePlatform(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Move")
	class ATargetPoint* StartPoint;
	UPROPERTY(EditAnywhere, Category = "Move")
	class ATargetPoint* EndPoint;

	UPROPERTY(EditAnywhere, Category = "Move")
	float MovementSpeed = 100;

	UPROPERTY(EditAnywhere, Category = "Move")
	float MoveDistanceWithoutEndPoint = 1000;

	UPROPERTY(EditAnywhere, Category = "Move|Return")
	bool bShouldReturn = true;
	// Negative value for infinite returns
	UPROPERTY(EditAnywhere, Category = "Move|Return", meta = (EditCondition = "bShouldReturn"))
	int NumOfReturns = 3;

	FVector StartLocation;
	FVector MoveDirectionUnitVector;

	float MoveDistance;
	float CurrentMoveDistance;


	void SetNullPoints();

	void CheckIfReachTargetPoint();

	bool ShouldPlatformReturn() const;

	bool ReachedEndPoint() const;

};
