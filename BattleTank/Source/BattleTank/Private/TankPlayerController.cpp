// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) 
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" The tank don't have a Aiming Component"))
	}

}

void ATankPlayerController::SetPawn(APawn *  InPawn) {

	Super::SetPawn(InPawn);

	if (InPawn) 
	{
			ATank * PossedTank = Cast<ATank>(InPawn);
			if (!ensure(PossedTank)) { return; }
			PossedTank->DeathDelegate.AddUniqueDynamic(this, &ATankPlayerController::OnDeathTank);
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto PawnPossed = GetPawn();

	if (PawnPossed) {

		auto AimingComponent = PawnPossed->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return; }

		FVector HitLocation = FVector(0, 0, 0);

		if (GetSightRayHitLocation(HitLocation))
		{
			AimingComponent->AimAt(HitLocation);
		}
	}
}

void ATankPlayerController::OnDeathTank()
{
	
	auto * PossedPawn = GetPawnOrSpectator();
	if (PossedPawn)
	{
		StartSpectatingOnly();
	}
}

//Get world location of linetrace trhough crosshair and return true if hit somthing 
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{

	//Find CrossHair Location
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenCrossHairLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	//Deproject Screen position to world location 
	FVector RayWorldDirection;
	if (GetLookDirection(ScreenCrossHairLocation, RayWorldDirection))
	{
		//Make Line trace trough crosshair 	
		return GetLookHitLocation(RayWorldDirection, HitLocation);
	}

	return false;
}


//Get vector direction of we are looking
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	bool ItWork = false;

	FVector CameraWorldPosition;

	ItWork = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldPosition, LookDirection);

	return ItWork;
}

//Get location of line trace by direction of we are loking 
bool ATankPlayerController::GetLookHitLocation(FVector Direction, FVector &HitLocation) const
{

	FVector StartPos = PlayerCameraManager->GetCameraLocation();
	FVector EndPos = StartPos + (Direction * Range);
	
	FHitResult HitResault;

	if (GetWorld()->LineTraceSingleByChannel(HitResault, StartPos, EndPos, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResault.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}
	
}

