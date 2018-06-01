// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	
	void AimTowardsCrosshair();

	UPROPERTY(EditAnyWhere)
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditAnyWhere)
	float CrossHairYLocation = 0.4f;

	UPROPERTY(EditAnyWhere)
	float Range = 1000000.0f;
	

private :

	bool GetSightRayHitLocation(FVector &HitLocation )const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

	bool GetLookHitLocation(FVector Direction, FVector &HitLocation) const;

};
