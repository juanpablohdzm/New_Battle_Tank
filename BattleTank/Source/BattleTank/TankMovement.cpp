// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankTrack.h"
#include "TankMovement.h"


void UTankMovement::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("move forward %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovement::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if(!LeftTrackToSet || !RightTrackToSet)
	{
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
