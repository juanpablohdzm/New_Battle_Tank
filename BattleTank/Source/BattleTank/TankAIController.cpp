// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


ATank * ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank * AIPawn = GetAIControlledTank();
	ATank * PlayerTank = GetPlayerTank();
}

ATank * ATankAIController::GetPlayerTank() const
{
	 auto PlayerPawn=GetWorld()->GetFirstPlayerController()->GetPawn();
	 if (PlayerPawn)
	 {
		 UE_LOG(LogTemp, Warning, TEXT("Player Controller is found: %s"),*PlayerPawn->GetName());
	 }
	 else
	 {
		 UE_LOG(LogTemp, Warning, TEXT("Player Controller not found"));
		 return nullptr;
	 }
	 return Cast<ATank>(PlayerPawn);
}

