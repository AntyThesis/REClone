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
	
	UPROPERTY()
	UHealthComponent* HealthComponent;
	
	UPROPERTY()
	ARECloneCharacter* OwningCharacter;
	
	UPROPERTY(BlueprintReadOnly)
	EEffectType EffectType;
	
	UPROPERTY(BlueprintReadOnly)
	float EffectValue = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool UseItem(const EEffectType EffectTypeToUse,const float EffectValueToUse) const;
};
