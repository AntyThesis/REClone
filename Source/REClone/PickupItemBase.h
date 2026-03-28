// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemStructs.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItemBase.generated.h"

UCLASS()
class RECLONE_API APickupItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItemBase();
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FItemData ItemData;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
