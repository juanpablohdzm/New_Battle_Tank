// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AIPawn = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PlayerTank)
	{

		AIPawn->AimAt(PlayerTank->GetActorLocation());

		 //Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		AIPawn->fire();//TODO limit fire rate
	}
	else
		return;
}



