#pragma once


#include "CoreMinimal.h"
#include "EnemyStructs.generated.h"


USTRUCT(BlueprintType)
struct FEnemyData //: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStats")
	FName EnemyID;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStats")
	FText EnemyName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStats")
	UStaticMesh* StaticMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStats")
	float MaxHealth;
	
};