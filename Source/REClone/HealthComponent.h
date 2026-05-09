// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECLONE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	// Declare the maximum health this component can have
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MaxHealth;
	
	// Declare the current health of this component
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float CurrentHealth;
	
	//Declare OnHealthChanged delegate
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Declare function to affect health
	UFUNCTION(BlueprintCallable)
	bool AffectHealth(const float HealthChangeAmount);
};
