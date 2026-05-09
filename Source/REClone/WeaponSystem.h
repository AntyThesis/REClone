// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystem.generated.h"

class UInventoryComponent;
class ARECloneCharacter;
class AGunProjectile;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECLONE_API UWeaponSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSystem();
	
	// "Owning Character" of this component
	UPROPERTY()
	ARECloneCharacter* OwningCharacter;
	
	// The row handle for this weapons ammo
	UPROPERTY(VisibleAnywhere)
	FDataTableRowHandle AmmoItemRow;
	
	// Projectile class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TSubclassOf<AGunProjectile> ProjectileClass;
	

	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Fire Weapon
	virtual void FireWeapon();
	
	// Try to affect the ammo of the "shooting character"
	virtual void RequestAffectAmmo(const FDataTableRowHandle& AmmoType,const int Amount) const;
		
};
