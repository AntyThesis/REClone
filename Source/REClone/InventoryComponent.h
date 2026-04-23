// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemStructs.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemAdded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemRemoved);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECLONE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	
	// Delegate for "Adding an item"
	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;
	
	// Delegate for "Removing an item"
	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	
	// Inventory
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FInventorySlot> InventorySlots;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SlotMaximum = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	// Function to add item to the list of inventory slots
	UFUNCTION( BlueprintCallable )
	bool AddItem(const FInventorySlot& InventorySlotToAdd);
	
	// Function to remove item from the list of inventory slots
	UFUNCTION( BlueprintCallable )
	void RemoveItem(const FInventorySlot& InventorySlotToRemove);

	
	UFUNCTION( BlueprintCallable )
	void PrintInventory();
		
};
