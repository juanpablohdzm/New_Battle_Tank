// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
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

	//First Fire after reload
	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		FiringStatus = EFiringStatus::Reload;
	else
		if (IsBarrelMoving())
			FiringStatus = EFiringStatus::Aiming;
		else
			FiringStatus = EFiringStatus::Locked;
	
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Turret))
	{
		return;
	}
	if (!ensure(Barrel))
	{
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
		AimDirection = OutLanchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	

	Barrel->ElevateBarrel(DeltaRotator.Pitch); 
	Turret->MoveTurret(DeltaRotator.Yaw);
}

void UTankAimingComponent::fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	if (FiringStatus != EFiringStatus::Reload)
	{
		AProjectile * Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection,0.01);
}


