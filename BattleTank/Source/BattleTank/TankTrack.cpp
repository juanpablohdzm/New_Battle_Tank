// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("moving throttle at %f"),Throttle);

	//TODO clamp throttle
	FVector ForceApplied = GetForwardVector()*Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
		
			UPrimitiveComponent * TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
			TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	
		
}



