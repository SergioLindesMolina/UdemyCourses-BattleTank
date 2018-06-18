// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack) 
{
	this->leftTrack = leftTrack;
	this->rightTrack = rightTrack;
}


void UTankMovementComponent::IntentMoveForward(float Throw) 
{
	if (!ensure(leftTrack && rightTrack)) { return; }

	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntentMoveRight(float Throw) 
{
	if (!ensure(leftTrack && rightTrack)) { return; }

	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(-Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector forwardIntentVelocity = MoveVelocity.GetSafeNormal();

	float forwardThrow = FVector::DotProduct(tankForward, forwardIntentVelocity);
	IntentMoveForward(forwardThrow);

	float rightThrow = FVector::CrossProduct(tankForward, forwardIntentVelocity).Z;
	IntentMoveRight(rightThrow);
}

