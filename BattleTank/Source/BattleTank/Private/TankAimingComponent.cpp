// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float ProjectileStartSpeed)
{
	if (Barrel == nullptr) { return; } 

	FVector Out_ProjectileLaunchVelocity = FVector::ZeroVector;
	FVector StartPos = Barrel->GetSocketLocation(FName("Projectile"));
	const FCollisionResponseParams ResponseParam;

	bool bSuggestPrV = false;
	
	bSuggestPrV = UGameplayStatics::SuggestProjectileVelocity(this, Out_ProjectileLaunchVelocity, StartPos, HitLocation, ProjectileStartSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace,ResponseParam);
	
	


	if (bSuggestPrV) 
	{
		FVector AimDirection = Out_ProjectileLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
	}


	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Rotate barrel vector direction to aim direction vector
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation =  AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Rotate(DeltaRotation.Yaw);
}