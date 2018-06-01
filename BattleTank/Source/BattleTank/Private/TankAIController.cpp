// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	ATank * AITank = GetTankAIControlled();

	ATank * PlayerTank = GetPlayerTank();

	//if (AITank) { UE_LOG(LogTemp, Warning, TEXT("The tank controlled is : %s"), *AITank->GetName()); }
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Error"));
	//}
	//
	//if (PlayerTank){ UE_LOG(LogTemp, Warning, TEXT("The tank of the player is : %s"), *PlayerTank->GetName()); }
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Error not player found"));
	//}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetPlayerTank()) { return; }

	GetTankAIControlled()->AimAt(GetPlayerTank()->GetActorLocation());
	
}


ATank* ATankAIController::GetTankAIControlled() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
