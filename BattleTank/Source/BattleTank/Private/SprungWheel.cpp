// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	springConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring Constraint"));
	SetRootComponent(springConstraint);

	axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	axle->AttachToComponent(springConstraint, FAttachmentTransformRules::KeepRelativeTransform);

	wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	wheel->AttachToComponent(axle, FAttachmentTransformRules::KeepRelativeTransform);

	axleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	axleConstraint->AttachToComponent(axle, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	wheel->SetNotifyRigidBodyCollision(true);
	wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	if (GetAttachParentActor()) 
	{
		auto tankRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (!tankRoot) { return; }
		springConstraint->SetConstrainedComponents(tankRoot, NAME_None, axle, NAME_None);
		axleConstraint->SetConstrainedComponents(axle, NAME_None, wheel, NAME_None);
	}
	
	
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//Add force to the wheel 
	wheel->AddForce(axle->GetForwardVector() * totalForceThisFrame);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics) 
	{
		totalForceThisFrame = 0;
	}

}

void ASprungWheel::AddDrivingForce(float force)
{
	totalForceThisFrame += force;
}

