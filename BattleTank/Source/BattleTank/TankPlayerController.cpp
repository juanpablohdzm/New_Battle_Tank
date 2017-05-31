// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT(" Tank Player Controller Begin Play"));

	ATank * Tank = GetControlledTank();

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is found"), *Tank->GetFName().ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank is not found"));
	}
}


void ATankPlayerController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();

}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }

	//Get world location if linetrace through crosshair
	// if it hits the landscape
		//Tell controlled tank to aim that point 
}
