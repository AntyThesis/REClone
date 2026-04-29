// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem.h"

#include "RECloneCharacter.h"


// Sets default values for this component's properties
UWeaponSystem::UWeaponSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> TableObj(
	TEXT("/Game/TopDown/Blueprints/DT_ItemData.DT_ItemData"));
	
	if (TableObj.Succeeded())
	{
		AmmoItemRow.DataTable = TableObj.Object;
		AmmoItemRow.RowName = FName("Bullets");
	}
	// ...
}


// Called when the game starts
void UWeaponSystem::BeginPlay()
{
	Super::BeginPlay();
	
	OwningCharacter = Cast<ARECloneCharacter>(this->GetOwner());

	// ...
	
}


// Called every frame
void UWeaponSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponSystem::FireWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Black,"Weapon fired");
	RequestAffectAmmo(AmmoItemRow,1);
}

void UWeaponSystem::RequestAffectAmmo(const FDataTableRowHandle& AmmoType,const int Amount) const
{
	OwningCharacter->AffectAmmo(AmmoItemRow,Amount);
}

