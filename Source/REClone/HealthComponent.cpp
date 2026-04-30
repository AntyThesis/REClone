// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	MaxHealth = 100.0f;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

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
	if (CurrentHealth < MaxHealth)
	{	
		
		CurrentHealth += HealthChangeAmount;
		CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
	
		GEngine->AddOnScreenDebugMessage(
		-1,5.f, FColor::Green,
		FString::Printf(TEXT("Health: %f"), CurrentHealth));
	
	
		GEngine->AddOnScreenDebugMessage(
		-1, 5.f, FColor::Yellow,
		FString::Printf(TEXT("Heal Amount: %f"), HealthChangeAmount));
	
		
		OnHealthChanged.Broadcast();
		return true;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black,"Health is already full");
	return false;
}

