// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	float ElevationChange = FMath::Clamp(relativeSpeed,-1.0F,1.0F) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampElevation = FMath::Clamp(RawElevation, MinElevationDegrees, MaxElevationDegrees);
	
	SetRelativeRotation(FRotator(ClampElevation, 0, 0));

}

