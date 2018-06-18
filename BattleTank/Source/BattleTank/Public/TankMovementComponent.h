// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankTrack;

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Responsible of making the tank move
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack);

	UFUNCTION(BlueprintCallable)
	void IntentMoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntentMoveRight(float Throw);


private:
	
	// Called from pathfinding logic by ai controlers 
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


	UTankTrack* leftTrack = nullptr;
	UTankTrack* rightTrack = nullptr;
	
};
