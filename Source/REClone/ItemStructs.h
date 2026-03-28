// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStructs.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FText ItemName;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UTexture2D* ItemIcon;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMesh* ItemMesh;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	EffectEnum EffectType;
	
};