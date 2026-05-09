// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemEffectSystem.h"

#include "IDetailTreeNode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ItemInterface.h"
#include "RECloneCharacter.h"

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
	
	// Set the owning character and that characters health component
	OwningCharacter = Cast<ARECloneCharacter>(GetOwner());
	HealthComponent = Cast<UHealthComponent>(OwningCharacter->FindComponentByClass(UHealthComponent::StaticClass()));

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
	
	// Using an item has a different effect that depends on the effect type
	switch (EffectTypeToUse)
	{
		// Heal = Check for health component and if found heal the player
	case EEffectType::Heal:
		if (HealthComponent)
		{
			if (HealthComponent->AffectHealth(EffectValueToUse))
			{
				GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,"Heal Item Used");
				return true;
			}
			else
			{
				return false;
			}
		}
		break;
	
		// If the character successfully equips a weapon, success exit, if not, failure exit
	case EEffectType::EquipWeapon:
		GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,"Weapon Item Used");
		if (OwningCharacter->EquipWeapon())
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
		
		// Unlock the door
	case EEffectType::Unlock:
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,"Key Item Used");
		
			TArray<AActor*> OverlappingActors;
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			TArray<AActor*> ActorsToIgnore;
			
			bool ItemFound = false;
			
			ActorsToIgnore.Add(OwningCharacter);
			
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		
			UKismetSystemLibrary::SphereOverlapActors(GetWorld(), OwningCharacter->GetActorLocation(),100.f,
			ObjectTypes,AActor::StaticClass(),ActorsToIgnore,OverlappingActors);
		
			for (const auto Actor : OverlappingActors)
			{
				if (Actor->GetClass()->ImplementsInterface(UItemInterface::StaticClass()))
				{
					GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green, FString::Printf(TEXT("Array Length: %d"), OverlappingActors.Num()));
					if (IItemInterface::Execute_OnUnlock(Actor, OwningCharacter))
					{
						ItemFound = true;
						return ItemFound;
					}
				}
			}          
			
			return ItemFound;
			break;
		}	
		
		// The player equips the flashlight
	case EEffectType::EquipLight:
		OwningCharacter->EquipFlashlight();
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Emerald,"Flashlight Equipped");
		return true;
		break;
		
		// For items that have no effect ie bullets
	case EEffectType::NoEffect:
		return true;
		break;
		
		// Default case switch
	default:
		break;
	}
	return false;
}




