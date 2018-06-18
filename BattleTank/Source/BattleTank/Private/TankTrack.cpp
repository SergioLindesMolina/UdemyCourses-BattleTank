// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this,&UTankTrack::OnHit);

}

void UTankTrack::SetThrottle(float throttle) 
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + throttle, -1, 1);
}

void UTankTrack::DriveTank()
{
	FVector forceToApply = GetForwardVector() * CurrentThrottle * maxDrivingForce;

	
//DrawDebugLine(
//		GetWorld(),
//		GetComponentLocation(),
//		GetComponentLocation() + forceToApply,
//		FColor(255, 0, 0),
//		false, 5, 0,
//		12.333
//	);

	UPrimitiveComponent* tankBase = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankBase->AddForceAtLocation(forceToApply, GetComponentLocation());
}

void UTankTrack::ApplySidewaysForce( )
{
	// Corrrection to avoid  side ways slippage 
	// Slippage Speed 
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//  Aceleration requiered this frame
	auto DeltaTime = GetWorld()->DeltaTimeSeconds;
	auto correctionAceleration = -(slippageSpeed / DeltaTime) * GetRightVector();

	// force requiered 

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = tankRoot->GetMass() * correctionAceleration  * 0.5; // 0.5 because there are thow tracks

	tankRoot->AddForce(correctionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor* OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult& Hit) 
{
	
	DriveTank();
	// Correct Sideways movement of the tank appling force
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

