// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Turret)
	{
		UE_LOG(LogTemp, Warning, TEXT("Turret not found"));
		return;
	}
	if (!Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("BARREL not found"));
		return;
	}
	FVector OutLanchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLanchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace))//Calculate the OutLaunchVelocity
	{
		FVector AimDirection = OutLanchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		RotateTurretTowards(HitLocation);
		UE_LOG(LogTemp, Warning, TEXT("Aim Solution %f"), GetWorld()->GetTimeSeconds());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Solution %f"), GetWorld()->GetTimeSeconds());
	}
	
}

void UTankAimingComponent::SetTurretComponent(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::SetBarrelComponent(UTankBarrel * BarrelToSet)
{

	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	

	Barrel->ElevateBarrel(DeltaRotator.Pitch); 
}

void UTankAimingComponent::RotateTurretTowards(FVector RotateDirection)
{
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator RotateAsRotator = RotateDirection.Rotation();
	FRotator DeltaRotator = RotateAsRotator - TurretRotation;

	Turret->MoveTurret(DeltaRotator.Yaw);
}



