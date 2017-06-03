// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void ElevateBarrel(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category =Setup)
	float MaxDegreesPerSecond = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinDegrees = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegrees = 40.0f;


};
