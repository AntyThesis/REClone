// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystem.generated.h"

class UInventoryComponent;
class ARECloneCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECLONE_API UWeaponSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSystem();
	
	UPROPERTY()
	ARECloneCharacter* OwningCharacter;
	
	UPROPERTY(VisibleAnywhere)
	FDataTableRowHandle AmmoItemRow;
	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void FireWeapon();
	
	virtual void RequestAffectAmmo(const FDataTableRowHandle& AmmoType,const int Amount) const;
		
};
