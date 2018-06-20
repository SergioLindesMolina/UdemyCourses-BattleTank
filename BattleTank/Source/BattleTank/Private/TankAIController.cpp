// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::OnTankDeath()
{

	auto * PossedPawn = GetPawn();
	if (PossedPawn) 
	{
		PossedPawn->DetachFromControllerPendingDestroy();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{

	Super::SetPawn(InPawn);

	if (InPawn) 
	{
		ATank * PossedTank = Cast<ATank>(InPawn);
		if (!ensure(PossedTank)) { return; }
		PossedTank->DeathDelegate.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);

	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto controlledAimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	

	if (!ensure(PlayerTank || controlledAimComp)) { return; }


	if(PlayerTank && controlledAimComp) 
	{

		MoveToActor(PlayerTank, AceptanceRadius);
		controlledAimComp->AimAt(PlayerTank->GetActorLocation());
		
		if (controlledAimComp->GetFiringState() == EFiringState::Ready) 
		{
			controlledAimComp->Fire();
		}
	}
}



