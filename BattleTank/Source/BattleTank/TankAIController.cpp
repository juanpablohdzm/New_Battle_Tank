// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto AIPawn = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank && AIPawn)) { return; }
	
	UTankAimingComponent * AimingComponent = AIPawn->FindComponentByClass<UTankAimingComponent>();

	//Aim towards player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	 //Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	
	AimingComponent->fire();//TODO limit fire rate
	
}



