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
	
	
	switch (EffectTypeToUse)
	{
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
	case EEffectType::NoEffect:
		return true;
		break;
		
	default:
		break;
	}
	return false;
}




