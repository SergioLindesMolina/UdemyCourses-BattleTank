// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void  UTankTurret::Rotate(float relativeSpeed)
{
	auto RotationChangeAmount = FMath::Clamp(relativeSpeed, -1.0f, 1.0f) * MaxRotationPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawRotationChange = RelativeRotation.Yaw + RotationChangeAmount;

	SetRelativeRotation(FRotator(0, RawRotationChange, 0));

	
}

