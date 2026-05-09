// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GunProjectile.h"
#include "CoreMinimal.h"
#include "HealthInterface.h"
#include "GameFramework/Character.h"
#include "RECloneCharacter.generated.h"


class UInventoryComponent;
class UWeaponSystem;
class UHealthComponent;
class UItemEffectSystem;
class USpotLightComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFlashlightEquipped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightToggle);

UCLASS(Blueprintable)
class ARECloneCharacter : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

public:
	ARECloneCharacter();
	
	// Declare Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UInventoryComponent* InventoryComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UItemEffectSystem* ItemEffectSystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UWeaponSystem* WeaponSystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USpotLightComponent* Flashlight;
	
	
	
	// Declare delegates
	UPROPERTY(BlueprintAssignable)
	FOnEquip OnEquip;
	
	UPROPERTY(BlueprintAssignable)
	FOnLightToggle OnLightToggle;
	
	UPROPERTY(BlueprintAssignable)
	FOnFlashlightEquipped OnFlashlightEquipped;
	
	
	// Declare "Flashlight Equipped" variable
	bool FlashlightEquipped = false;
	
	
	
	// Declare the class of projectile to be fed into the "Fire Weapon" call
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<AGunProjectile> ProjectileInClass;
	

	
	
	
	
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	bool EquipWeapon();
	
	void EquipFlashlight();
	
	void ToggleFlashlight();
	
	void Interact();
	
	void FireWeaponRequest();
	
	void AffectAmmo(const FDataTableRowHandle& BulletsToRemove,const int Amount) const;
	
	virtual void ApplyHealthChange_Implementation(const float ChangeAmount) override;


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	
};

