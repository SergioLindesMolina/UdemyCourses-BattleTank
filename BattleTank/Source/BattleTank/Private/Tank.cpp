// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankCurrentHealth = TankMaxHealth;
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInsitigator, AActor * DamageCauser)
{
	
	int32 DamagePoints = FMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, TankMaxHealth);

	TankCurrentHealth -= DamageToApply;

	if (TankCurrentHealth <= 0) 
	{
		TankCurrentHealth = 0;
		DeathDelegate.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetPrecentangeHealth() const
{
	return (float)TankCurrentHealth / (float)TankMaxHealth;
}




