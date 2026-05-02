// Fill out your copyright notice in the Description page of Project Settings.


#include "Unlockable.h"

// Sets default values
AUnlockable::AUnlockable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));

}

// Called when the game starts or when spawned
void AUnlockable::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AUnlockable::OnUnlock_Implementation(ARECloneCharacter* UnlockingCharacter)
{
	
	if (!UnlockingCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green, "No 'UnlockingCharacter' found");
		return false;
	}
	
	OnUnlocked.Broadcast();
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green, "Door Unlocked");
	return true;
}

// Called every frame
void AUnlockable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

