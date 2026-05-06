#pragma once


#include "CoreMinimal.h"
#include "EnemyTypeEnum.h"
#include "EnemyStructs.generated.h"


USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	EEnemyType EnemyType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	FName EnemyID;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	FText EnemyName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	USkeletalMesh* SkeletalMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	float MaxHealth;
	
};

USTRUCT(BlueprintType)
struct FEnemyIdentity
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	FDataTableRowHandle EnemyRowHandle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Stats")
	int EnemyNumber;
};