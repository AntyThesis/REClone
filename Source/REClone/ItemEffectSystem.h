// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEnums.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.h"
#include "ItemEffectSystem.generated.h"

class ARECloneCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECLONE_API UItemEffectSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemEffectSystem();
	
	// A pointer to a health component
	UPROPERTY()
	UHealthComponent* HealthComponent;
	
	// A pointer to the character that owns this component
	UPROPERTY()
	ARECloneCharacter* OwningCharacter;
	
	// The effect type of the item
	UPROPERTY(BlueprintReadOnly)
	EEffectType EffectType;
	
	// The magnitude of the effect
	UPROPERTY(BlueprintReadOnly)
	float EffectValue = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//  Declaration of the "Use Item" function
	bool UseItem(const EEffectType EffectTypeToUse,const float EffectValueToUse) const;
};
