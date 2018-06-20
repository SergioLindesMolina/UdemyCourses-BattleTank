// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"


UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::SetThrottle(float throttle) 
{
	float CurrentThrottle = FMath::Clamp<float>(throttle, -1, 1);

	DriveTank(CurrentThrottle);
}

void UTankTrack::DriveTank(float CurrentThrottle)
{
	auto forceToApply = CurrentThrottle * maxDrivingForce;
	auto Wheels = GetWheels();
	auto forceByWheel = forceToApply / Wheels.Num();
	
	for (int i = 0; i < Wheels.Num(); i++)
	{
		Wheels[i]->AddDrivingForce(forceByWheel);
	}


	//UPrimitiveComponent* tankBase = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//tankBase->AddForceAtLocation(forceToApply, GetComponentLocation());
}


TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> trackWheels;
	
	TArray<USceneComponent*> spawnPoints;
	GetChildrenComponents(true, spawnPoints);
	
	for (int i = 0; i < spawnPoints.Num(); i++)
	{
		auto spawnPoint = Cast<USpawnPoint>(spawnPoints[i]);
		if (!spawnPoint) continue;

		auto wheel = Cast<ASprungWheel>(spawnPoint->GetActorSpawned());
		if (!wheel) continue;

		trackWheels.Add(wheel);
	}

	return trackWheels;
}


