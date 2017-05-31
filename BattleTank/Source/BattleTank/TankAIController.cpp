// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


ATank * ATankAIController::GetAIControlledTank()
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank * AIPawn = GetAIControlledTank();
	if (AIPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is found"), *AIPawn->GetFName().ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not found"));
	}
}

