// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AIPawn = GetAIControlledTank();
	PlayerTank = GetPlayerTank();
	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		
		AIPawn->AimAt(PlayerTank->GetActorLocation());

		//TODO Move towards the player

		// Fire to the player
	}
	else
		return;
}



ATank * ATankAIController::GetPlayerTank() const
{
	 auto PlayerPawn=GetWorld()->GetFirstPlayerController()->GetPawn();
	 if (!PlayerPawn)
	 {
		 UE_LOG(LogTemp, Warning, TEXT("Player Controller not found"));
		 return nullptr;
	 }
	 return Cast<ATank>(PlayerPawn);
}

ATank * ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

