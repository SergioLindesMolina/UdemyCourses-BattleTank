// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Classes/PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);
	
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast "));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast "));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion"));
	RadialForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}
// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	// Set thins in begin play avoid some errors that happen when you do the same in the constructor
	//https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1377430-oncomponenthit-isn-t-working
	//Don't set things in the constructor, they're liable to get stomped by construction scripts / actor load from disk. PostLoad / OnBeginPlay are fairly safe spots to do any initialization code.
	
	if (CollisionMesh) {
		CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHitObject); 
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	ProjectileMovement->Activate();
}

void AProjectile::OnHitObject(UPrimitiveComponent * HitComponent, AActor* OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	RadialForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage
	(this, ProjectileDamage, GetActorLocation(), RadialForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());


	FTimerHandle tmHandle;
	GetWorld()->GetTimerManager().SetTimer(tmHandle, this, &AProjectile::DestroyProjectile, timeToDestroy);
	
}

void AProjectile::DestroyProjectile() {
	Destroy(this);
}


