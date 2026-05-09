// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "ItemEnums.h" 
#include "ItemStructs.generated.h"


USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	
	// Name of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FName ItemID; 
	
	// Icon for the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UTexture2D* ItemIcon;
	
	// Mesh for the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UStaticMesh* ItemMesh;
	
	// Effect type from enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	EEffectType EffectType;
	
	// Numerical effect value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float EffectValue;
	
	// Maximum amount that can occupy one inventory slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int MaxQuantity;
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()
	
	// Row handle that contains all the item data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySlotData")
	FDataTableRowHandle RowHandle;
	
	// The quantity of the item currently in the players inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySlotData")
	int Quantity;
};