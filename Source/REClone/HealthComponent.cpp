// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Initialize max health
	MaxHealth = 100.0f;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//Set starting health
	CurrentHealth = MaxHealth;
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UHealthComponent::AffectHealth(const float HealthChangeAmount)
{
	// Check if the player has missing health or whether its a heal or damage
	if (CurrentHealth < MaxHealth || HealthChangeAmount < 0.0f)
	{	
		// Affect the health
		CurrentHealth += HealthChangeAmount;
		CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
	
		// Debug strings
		GEngine->AddOnScreenDebugMessage(
		-1,5.f, FColor::Green,
		FString::Printf(TEXT("Health: %f"), CurrentHealth));
		
		GEngine->AddOnScreenDebugMessage(
		-1, 5.f, FColor::Yellow,
		FString::Printf(TEXT("Heal Amount: %f"), HealthChangeAmount));
	
		// Broadcast the OnHealthChanged delegate and success exit
		OnHealthChanged.Broadcast();
		return true;
	}
	// Heal if the player is missing health AND if this is a heal, then failure exit
	if (CurrentHealth >= MaxHealth && HealthChangeAmount > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black,"Health is already full");
		return false;
	}
	return false;
}

