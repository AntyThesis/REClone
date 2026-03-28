// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "ItemEnums.h" 
#include "ItemStructs.generated.h"


USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
	
	// Name of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FText ItemName;
	
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
};