// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum to controll aiming state 
UENUM()
enum class EFiringState : uint8 
{
	Reloading,
	Aiming,
	Ready,
	OutOfAmmo

};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	EFiringState GetFiringState() const;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileStartSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "States")
	EFiringState currentState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 3;

private:	

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	double lastFireTime = 0;

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	FVector AimDirection;
};
