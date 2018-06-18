// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "Engine/World.h"
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


void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// delay to avoid fire whent the game starts 
	lastFireTime = FPlatformTime::Seconds();
	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTime;

	if (RoundsLeft <= 0)
	{
		currentState = EFiringState::OutOfAmmo;
	}
	else if (!isReloaded) 
	{
		currentState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		currentState = EFiringState::Aiming;
	}
	else 
	{
		currentState = EFiringState::Ready;
	}

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure (Barrel)) { return; } 

	FVector Out_ProjectileLaunchVelocity = FVector::ZeroVector;
	FVector StartPos = Barrel->GetSocketLocation(FName("Projectile"));
	const FCollisionResponseParams ResponseParam;

	bool bSuggestPrV = false;
	
	bSuggestPrV = UGameplayStatics::SuggestProjectileVelocity(this, Out_ProjectileLaunchVelocity, StartPos, HitLocation, ProjectileStartSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace,ResponseParam);
	
	if (bSuggestPrV) 
	{
		AimDirection = Out_ProjectileLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);		
	}	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }	

	//Rotate barrel vector direction to aim direction vector
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation =  AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);

	//UE_LOG(LogTemp, Warning, TEXT("Delta Rotation %s "), *DeltaRotation.ToString())

	if (FMath::Abs(DeltaRotation.Yaw) < 180) 
	{
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotation.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return true; }

	if (Barrel->GetForwardVector().Equals(AimDirection, 0.01f)) 
	{
		return false;
	}

	return true;
}

void UTankAimingComponent::Fire()
{

	if (!ensure(ProjectileBlueprint)) { return; } // avoid crash by null property 
	if (!ensure(Barrel)) { return; }
	
	
	
	if (currentState == EFiringState::Aiming || currentState == EFiringState::Ready)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>
			(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		
		Projectile->LaunchProjectile(ProjectileStartSpeed);
		lastFireTime = FPlatformTime::Seconds(); // FPlatformTime::Seconds() time pased in seconds since some time befor, not specified when 
		RoundsLeft--;
	}
}

int32 UTankAimingComponent::GetRoundsLeft () const
{
	return RoundsLeft;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return currentState;
}
