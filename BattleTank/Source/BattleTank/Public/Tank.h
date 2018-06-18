// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 TankMaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 TankCurrentHealth;

private:	

	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public :

	FDeathDelegate DeathDelegate;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController * EventInsitigator, AActor *DamageCauser) override;
	
	//Return healt in a precentage between 0 and 1 
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetPrecentangeHealth() const;
	

};
