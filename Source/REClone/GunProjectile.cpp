// Fill out your copyright notice in the Description page of Project Settings.


#include "GunProjectile.h"
#include "RECloneCharacter.h"

// Sets default values
AGunProjectile::AGunProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Initialize mesh and collision
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	Mesh->SetupAttachment(RootComponent);
	
	
	// Initialize settings for the projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	
	CollisionBox->OnComponentHit.AddDynamic(this, &AGunProjectile::OnBoxHit);
	
	
}

// Called when the game starts or when spawned
void AGunProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunProjectile::OnBoxHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this)
		return;

	// Ignore shooter
	if (OtherActor == GetOwner())
		return;

	// If it can take damage
	if (OtherActor->GetClass()->ImplementsInterface(UHealthInterface::StaticClass()))
	{
		IHealthInterface::Execute_ApplyHealthChange(OtherActor, -20.f);
		
		// You can use Hit.ImpactPoint for effects if needed
		Destroy();
		return;
	}

	// Wall / environment hit
	Destroy();
}