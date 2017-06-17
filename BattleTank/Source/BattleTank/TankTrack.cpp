// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector RightVector = GetRightVector();
	float SlippageSpeed = FVector::DotProduct(RightVector, GetComponentVelocity());
	
	// Work-out the requiered acceleration this frame to correct
	FVector CorrectAceleration = -SlippageSpeed / DeltaTime * RightVector;

	//Calculates and apply sidewars (f = ma)
	UStaticMeshComponent * TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce=(TankRoot->GetMass() * CorrectAceleration);
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector()*Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
		
	UPrimitiveComponent * TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	
		
}



