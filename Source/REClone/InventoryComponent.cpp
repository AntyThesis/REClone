// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ItemEffectSystem = Cast<UItemEffectSystem>(GetOwner()->GetComponentByClass(UItemEffectSystem::StaticClass()));
	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


bool UInventoryComponent::AddItem(const FInventorySlot& InventorySlotToAdd)
{
	const FItemData* Data = InventorySlotToAdd.RowHandle.GetRow<FItemData>(TEXT("AddItem"));
	if (!Data) return false;

	int32 RemainingQuantity = InventorySlotToAdd.Quantity;
	bool bItemAdded = false;

	// 🔥 STEP 1: Fill existing stacks (ALWAYS allowed)
	for (auto& Slot : InventorySlots)
	{
		if (Slot.RowHandle.RowName == InventorySlotToAdd.RowHandle.RowName)
		{
			if (Slot.Quantity >= Data->MaxQuantity)
			{
				continue;
			}

			int32 SpaceLeft = Data->MaxQuantity - Slot.Quantity;
			int32 AmountToAdd = FMath::Min(SpaceLeft, RemainingQuantity);

			if (AmountToAdd > 0)
			{
				Slot.Quantity += AmountToAdd;
				RemainingQuantity -= AmountToAdd;
				bItemAdded = true;
			}

			if (RemainingQuantity <= 0)
			{
				OnItemAdded.Broadcast();
				PrintInventory();
				return true;
			}
		}
	}

	// 🔥 STEP 2: Create new stacks ONLY if we have room
	while (RemainingQuantity > 0)
	{
		if (InventorySlots.Num() >= SlotMaximum)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, "Inventory Full");
			break; // stop trying to add new stacks
		}

		FInventorySlot NewSlot = InventorySlotToAdd;

		int32 StackAmount = FMath::Min(Data->MaxQuantity, RemainingQuantity);

		NewSlot.Quantity = StackAmount;
		InventorySlots.Add(NewSlot);

		RemainingQuantity -= StackAmount;
		bItemAdded = true;
	}

	// 🔥 STEP 3: Only broadcast if something changed
	if (bItemAdded)
	{
		OnItemAdded.Broadcast();
		PrintInventory();
		return true;
	}

	return false;
}

bool UInventoryComponent::HasBullets() const
{
	static const FName BulletsName ("Bullets");
	
	for (auto& Slot : InventorySlots)
	{
		if (Slot.RowHandle.RowName == BulletsName)
		{
			return true;
		}
	}
	return false;
}


// When "Remove item" is called
bool UInventoryComponent::RemoveItem(const FDataTableRowHandle& RowHandle, int32 Quantity)
{
	for (int32 i = 0; i < InventorySlots.Num(); i++)
	{
		// Compare using RowHandle (identity)
		if (InventorySlots[i].RowHandle.RowName == RowHandle.RowName)
		{
			InventorySlots[i].Quantity -= Quantity;

			// Clamp to 0 minimum
			if (InventorySlots[i].Quantity <= 0)
			{
				InventorySlots.RemoveAt(i);
			}

			OnItemRemoved.Broadcast();
			PrintInventory();
			return true;
		}
	}
	return false;
}

void UInventoryComponent::PrintInventory()
{
	if (GEngine)
	{
		for (int32 i = 0; i < InventorySlots.Num(); i++)
		{
			const FItemData* Data = InventorySlots[i].RowHandle.GetRow<FItemData>(TEXT("PrintInventory"));

			if (!Data)
			{
				continue;
			}

			FString Name = Data->ItemID.ToString();
			int32 Quantity = InventorySlots[i].Quantity;

			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Yellow,
				FString::Printf(TEXT("Item: %s | Qty: %d"), *Name, Quantity)
			);
		}
	}
}

bool UInventoryComponent::RequestUse(const FInventorySlot& InventorySlotToRequest)
{
	if (!ItemEffectSystem)
	{
		GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Red,"No ItemEffectSystem found");
		return false;
	}
	
	const FItemData* Data = InventorySlotToRequest.RowHandle.GetRow<FItemData>(TEXT("GetData"));
	
	if (!Data)
	{
		GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Red,"No Data found");
		return false;
	}
	
	
	if (ItemEffectSystem->UseItem( Data->EffectType, Data->EffectValue))
	{
		if (InventorySlotToRequest.RowHandle.GetRow<FItemData>(TEXT("GetData"))->EffectType != EEffectType::NoEffect)
		{		
			RemoveItem(InventorySlotToRequest.RowHandle, InventorySlotToRequest.Quantity);
			return true;
		}
		if (InventorySlotToRequest.RowHandle.GetRow<FItemData>(TEXT("GetData"))->EffectType == EEffectType::NoEffect)
		{
			return true; 
		}
	}
	GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Red,"Use Item failed");
		return false;
}



