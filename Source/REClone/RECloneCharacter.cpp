// Copyright Epic Games, Inc. All Rights Reserved.

#include "RECloneCharacter.h"
#include "PickupItemBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "WeaponSystem.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

ARECloneCharacter::ARECloneCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	
	// Instantiate the components
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(FName("Inventory Component"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("Health Component"));
	ItemEffectSystem = CreateDefaultSubobject<UItemEffectSystem>(FName("Item Effect System"));
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(FName("Flashlight Component"));
	
	//Set up Flashlight component
	Flashlight->SetupAttachment(RootComponent);
	Flashlight->SetVisibility(false);
}

void ARECloneCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ARECloneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Bind the input actions
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ARECloneCharacter::Interact);
	PlayerInputComponent->BindAction("Fire Weapon",IE_Pressed,this, &ARECloneCharacter::FireWeaponRequest);
	PlayerInputComponent->BindAction("ToggleFlashlight",IE_Pressed,this, &ARECloneCharacter::ToggleFlashlight);
}

bool ARECloneCharacter::EquipWeapon() 
{
	// Set the weapon system
	WeaponSystem = Cast<UWeaponSystem>(AddComponentByClass(UWeaponSystem::StaticClass(), false,FTransform::Identity,false));
	
	
	// If there is a valid weapon system, set the projectile class and broadcast the "OnEquip" delegate and success exit
	if ( WeaponSystem)
	{
		WeaponSystem->ProjectileClass = ProjectileInClass;
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Emerald,"Weapon Equipped");
		OnEquip.Broadcast();
		return true;
	}
	
	// If there is no valid weapon system, failure exit
	return false;
}

void ARECloneCharacter::EquipFlashlight()
{
	// Set "FlashlightEquipped" to true and broadcast the "OnFlashlightEquipped" delegate
	FlashlightEquipped = true;
	OnFlashlightEquipped.Broadcast();
	
}

void ARECloneCharacter::ToggleFlashlight()
{
	// If there is a valid flashlight, Toggle it on or off
	if (FlashlightEquipped)
	{
		if (Flashlight->GetVisibleFlag() == false)
		{
			Flashlight->SetVisibility(true);
			OnLightToggle.Broadcast();
		}
		else
		{
			Flashlight->SetVisibility(false);
			OnLightToggle.Broadcast();
		}
	
	}
	// if there is no valid flashlight throw an error
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,"Flashlight not equipped");
	}
}

void ARECloneCharacter::Interact()
{
	// Set the overlap parameters
	TArray<AActor*> OverlappingActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

	
	// Overlap to check for interactables
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		GetActorLocation(),
		100.f,
		ObjectTypes,
		APickupItemBase::StaticClass(),
		TArray<AActor*>(),
		OverlappingActors
	);
	// Draw a matching debug sphere
	DrawDebugSphere(GetWorld(), GetActorLocation(), 100.f, 12, FColor::White, false, 5.f);

	// Check to see if there are any overlapping actors 
	if (OverlappingActors.Num() > 0)
	{
		// Check to see if the first overlapped actor is a pickup item
		if (APickupItemBase* PickupItem = Cast<APickupItemBase>(OverlappingActors[0]))
		{
			// Create an inventory slot to add and set its variables
			FInventorySlot InventorySlotToAdd;
			InventorySlotToAdd.RowHandle = PickupItem->SlotData.RowHandle;
			InventorySlotToAdd.Quantity = PickupItem->SlotData.Quantity;
	
			// Check to see if the inventory successfully added the item
			if (InventoryComponent->AddItem(InventorySlotToAdd))
			{
				// If it did call the item interface if that item implements it
				if (PickupItem->GetClass()->ImplementsInterface(UItemInterface::StaticClass()))
				{
					IItemInterface::Execute_OnPickup(PickupItem, this);
				}
			}
		}
	}
}

void ARECloneCharacter::FireWeaponRequest()
{
	
	// Check to see if there is a valid weapon system
	if (WeaponSystem != nullptr)
	{
		// Check to see if there are any bullets in the inventory
		if (!InventoryComponent->HasBullets())
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,"No bullets in inventory");
		}
		else
		{
			WeaponSystem->FireWeapon();
		}
	
	}
	// If there is not a valid weapon system throw an error
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,"No weapon equipped");
	}
}

void ARECloneCharacter::AffectAmmo(const FDataTableRowHandle& BulletsToRemove,const int Amount) const
{
	// Check to see if there is a valid inventory component and if so remove the bullets
	if (InventoryComponent)
	{
		InventoryComponent->RemoveItem(BulletsToRemove,Amount);
	}
}

void ARECloneCharacter::ApplyHealthChange_Implementation(const float ChangeAmount)
{
	// Check to see if there is a valid health component. If so, affect health, if not, throw an error
	if (HealthComponent)
	{
		HealthComponent->AffectHealth(ChangeAmount);
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,"Damage Applied");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,"No Health Component found");
	}
	
}
