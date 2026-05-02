// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInterface.h"
#include "GameFramework/Actor.h"
#include "Unlockable.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnlocked);

UCLASS()
class RECLONE_API AUnlockable : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnlockable();
	
	UPROPERTY(BlueprintAssignable)
	FOnUnlocked OnUnlocked;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual bool OnUnlock_Implementation(ARECloneCharacter* UnlockingCharacter) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
