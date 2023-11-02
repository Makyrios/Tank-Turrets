// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.generated.h"

UCLASS(Abstract)
class TANKS_API ABaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpawner();
	

	virtual void Tick(float DeltaTime) override;
	virtual void SpawnObject() PURE_VIRTUAL(ThisClass::SpawnObject);
	virtual void SetObjectData() PURE_VIRTUAL(ThisClass::SetObjectData);
	

};
