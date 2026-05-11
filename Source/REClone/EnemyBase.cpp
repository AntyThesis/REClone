// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "HealthComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Instantiate a health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Set health on spawm
	SetHealth();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::SetHealth()
{
	//const FEnemyData* Data = Identity.EnemyRowHandle.GetRow<FEnemyData>(TEXT("Store Data"));
	
	// Store the enemy data 
	if (const FEnemyData* Data = Identity.EnemyRowHandle.GetRow<FEnemyData>(TEXT("Store Data")))
	{
		// Set the enemy's current and max health
		HealthComponent->MaxHealth = Data->MaxHealth;
		HealthComponent->CurrentHealth = Data->MaxHealth;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green,FString::Printf(TEXT("%f"), HealthComponent->MaxHealth));
	}

	
}

