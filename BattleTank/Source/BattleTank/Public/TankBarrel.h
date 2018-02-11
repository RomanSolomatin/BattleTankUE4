// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), hideCategories=("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void ElevateBarrel(float DegreesPerSecond);

	UPROPERTY(EditAnywhere, Category=Setup)
	float MaxDegreesPerSecond = 20;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0;
};