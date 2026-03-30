// Copyright Epic Games, Inc. All Rights Reserved.

#include "RECloneCharacter.h"


#include "ItemInterface.h"
#include "PickupItemBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
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
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(FName("Inventory Component"));
}

void ARECloneCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ARECloneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ARECloneCharacter::Interact);
}

void ARECloneCharacter::Interact()
{
	TArray<AActor*> OverlappingActors;
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(),GetActorLocation(),100.f,ObjectTypes,APickupItemBase::StaticClass(),TArray<AActor*>(),OverlappingActors);
	DrawDebugSphere(GetWorld(),GetActorLocation(),100.f,12,FColor::White,false,5.f);
	
	if (OverlappingActors.Num() > 0)
	{
		if (APickupItemBase* PickupItem = Cast<APickupItemBase>(OverlappingActors[0]))
		{
			FInventorySlot InventorySlotToAdd;
			
			InventorySlotToAdd.ItemData = PickupItem->ItemData;
			InventorySlotToAdd.Quantity = 1;
			
			InventoryComponent->AddItem(InventorySlotToAdd);
			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					5.f,
					FColor::Cyan,
					FString::Printf(
						TEXT("Item: %s | Qty: %d"),
						*InventorySlotToAdd.ItemData.ItemID.ToString(),
						InventorySlotToAdd.Quantity));*/
			
				if (PickupItem->GetClass()->ImplementsInterface(UItemInterface::StaticClass()))
				{
					IItemInterface::Execute_OnPickup(PickupItem);
				}
			}
		}
	}

