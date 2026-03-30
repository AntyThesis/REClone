// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemBase.h"



// Sets default values
APickupItemBase::APickupItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	// Add static mesh component and box collision
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));

}

// Called when the game starts or when spawned
void APickupItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// IItemInterface Event Implementation
void APickupItemBase::OnPickup_Implementation()
{
	Destroy();
}

