// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "ItemEnums.generated.h"

// This macro exposes the enum to Blueprints
UENUM(BlueprintType)
enum class EEffectType : uint8

{
	Heal UMETA(DisplayName = "Heal"),
	EquipWeapon UMETA(DisplayName = "EquipWeapon"),
	Unlock UMETA(DisplayName = "Unlock"),
	
};
