// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public :

	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float throttle);
	
	UPROPERTY(EditDefaultsOnly)
	float maxDrivingForce = 400.000f; // Assuming a tank with a mas of 40 tones

private:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor* OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewaysForce();

	void DriveTank();

	float CurrentThrottle = 0;



};
