#pragma once

#include "CoreMinimal.h"
#include "EnemyTypeEnum.generated.h"

// This macro exposes the enum to Blueprints
UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	SlowEnemy UMETA(DisplayName = "Slow Enemy"),
	BaseEnemy UMETA(DisplayName = "Base Enemy"),
	FastEnemy UMETA(DisplayName = "Fast Enemy")
};