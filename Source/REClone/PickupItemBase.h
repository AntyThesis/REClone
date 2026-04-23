// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemInterface.h"
#include "RECloneCharacter.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PickupItemBase.generated.h"

UCLASS()
class RECLONE_API APickupItemBase : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItemBase();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* BoxComponent;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ItemDataHandle;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	// IItemInterface override declaration
	virtual bool OnPickup_Implementation(ARECloneCharacter* Interactor) override;

};
