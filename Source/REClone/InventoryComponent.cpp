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
	for (int32 i = 0; i < InventorySlots.Num(); i++)
	{
		if (InventorySlots[i].ItemData.ItemName.EqualTo(InventorySlotToAdd.ItemData.ItemName))
		{
			InventorySlots[i].Quantity += InventorySlotToAdd.Quantity;
			
			if (InventorySlots[i].Quantity > InventorySlots[i].ItemData.MaxQuantity)
			{
				InventorySlots[i].Quantity = InventorySlots[i].ItemData.MaxQuantity;
				OnItemAdded.Broadcast();
			}
			return;
		}
		
	}
	InventorySlots.Add(InventorySlotToAdd);
	OnItemAdded.Broadcast();
}


// When "Remove item" is called
void UInventoryComponent::RemoveItem(const FInventorySlot& InventorySlotToRemove)
{
	for (int32 i = 0; i < InventorySlots.Num(); i++)
	{
		if (InventorySlots[i].ItemData.ItemName.EqualTo(InventorySlotToRemove.ItemData.ItemName))
		{
			InventorySlots[i].Quantity -= InventorySlotToRemove.Quantity;
		
			
			if (InventorySlots[i].Quantity <= 0)
			{
				InventorySlots.RemoveAt(i);
				
			}
			OnItemRemoved.Broadcast();
			return;
		}
	}
}

