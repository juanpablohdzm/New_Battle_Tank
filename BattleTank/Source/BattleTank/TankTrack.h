// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  TankTrack is used to set maximum driving force, and add to apply forces to the tank
 */
UCLASS(meta =(BluePrintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:

	UTankTrack();

	

	UFUNCTION(BluePrintCallable, Category= Input)
	void SetThrottle(float Throttle);

	void DriveTrack();

	//Max Force per track 
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.f;


private:
	void ApplySidewaysForce();
	void BeginPlay() override;
	float CurrentThrottle = 0;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
