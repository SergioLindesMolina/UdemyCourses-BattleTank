// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
class UProjectileMovementComponent;
class URadialForceComponent;
UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
private:	
	// Sets default values for this actor's properties
	AProjectile();

	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent * CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent * LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent * ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere , Category = "Components")
	URadialForceComponent * RadialForce = nullptr;

	void DestroyProjectile();

	UFUNCTION()
	void OnHitObject(UPrimitiveComponent * HitComponent, AActor* OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Destroy")
	float timeToDestroy = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float ProjectileDamage = 20;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float speed);
	
};
