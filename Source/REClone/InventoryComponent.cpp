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

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// When "Add Item" is called
void UInventoryComponent::AddItem(const FInventorySlot& InventorySlotToAdd)
{
	for (auto& Slot : InventorySlots)
	{
		if (Slot.RowHandle.RowName == InventorySlotToAdd.RowHandle.RowName)
		{
			const FItemData* Data = Slot.RowHandle.GetRow<FItemData>(TEXT("AddItem"));
			if (!Data) return;

			Slot.Quantity += InventorySlotToAdd.Quantity;
			Slot.Quantity = FMath::Clamp(Slot.Quantity, 0, Data->MaxQuantity);

			OnItemAdded.Broadcast();
			PrintInventory();
			return;
		}
	}

	InventorySlots.Add(InventorySlotToAdd);
	OnItemAdded.Broadcast();
	PrintInventory();
}

// When "Remove item" is called
void UInventoryComponent::RemoveItem(const FInventorySlot& InventorySlotToRemove)
{
	for (int32 i = 0; i < InventorySlots.Num(); i++)
	{
		// Compare using RowHandle (identity)
		if (InventorySlots[i].RowHandle.RowName == InventorySlotToRemove.RowHandle.RowName)
		{
			InventorySlots[i].Quantity -= InventorySlotToRemove.Quantity;

			// Clamp to 0 minimum
			if (InventorySlots[i].Quantity <= 0)
			{
				InventorySlots.RemoveAt(i);
			}

			OnItemRemoved.Broadcast();
			PrintInventory();
			return;
		}
	}
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

