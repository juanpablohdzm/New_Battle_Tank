// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovement.generated.h"

class ATank;
class UTankTrack;
/**
 * Responsible from driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovement : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;

	
};
