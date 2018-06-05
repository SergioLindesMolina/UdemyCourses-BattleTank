// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle) 
{

	FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%f thorttle is %f"), *name, throttle);
}

