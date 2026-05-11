#pragma once


#include "CoreMinimal.h"
#include "EnemyTypeEnum.h"
#include "EnemyStructs.generated.h"


USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_BODY()
	
	// Type of Enemy
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	EEnemyType EnemyType;
	
	// ID of enemy
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	FName EnemyID;
	
	// Name of enemy
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	FText EnemyName;
	
	// Skeletal mesh asset
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	USkeletalMesh* SkeletalMesh;
	
	// Enemy max health
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	float MaxHealth;
	
};

USTRUCT(BlueprintType)
struct FEnemyIdentity
{
	GENERATED_BODY()
	// Enemy table row handle
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	FDataTableRowHandle EnemyRowHandle;
	
	// Unique number ID
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	int EnemyNumber;
};