// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEffectSystem.h"

// Sets default values for this component's properties
UItemEffectSystem::UItemEffectSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemEffectSystem::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent = Cast<UHealthComponent>(GetOwner()->FindComponentByClass(UHealthComponent::StaticClass()));

	// ...
	
}


// Called every frame
void UItemEffectSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
bool UItemEffectSystem::UseItem(const EEffectType EffectTypeToUse, const float EffectValueToUse) const
{
	
	
	switch (EffectTypeToUse)
	{
	case EEffectType::Heal:
		if (HealthComponent)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,"Heal Item Used");
			HealthComponent->AffectHealth(EffectValueToUse);
			return true;
		}
		break;
	
	case EEffectType::EquipWeapon:
		GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,"Weapon Item Used");
		return true;
		break;
		
	case EEffectType::Unlock:
		GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,"Key Item Used");
		return true;
		break;
		
	case EEffectType::NoEffect:
		return true;
		break;
		
	default:
		break;
	}
	return false;
}




