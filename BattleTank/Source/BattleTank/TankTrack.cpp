// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySidewaysForce();
	DriveTrack();
	CurrentThrottle = 0.f;
}

void UTankTrack::ApplySidewaysForce()
{
	// Work-out the requiered acceleration this frame to correct
	FVector RightVector = GetRightVector();
	float SlippageSpeed = FVector::DotProduct(RightVector, GetComponentVelocity());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectAceleration = -SlippageSpeed / DeltaTime * RightVector;

	//Calculates and apply sidewars (f = ma)
	UStaticMeshComponent * TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectAceleration);
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.f, 1.f);
		
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector()* CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent * TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}



