// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem.h"
#include "RECloneCharacter.h"
#include "GunProjectile.h"


// Sets default values for this component's properties
UWeaponSystem::UWeaponSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// Find the item data table
	static ConstructorHelpers::FObjectFinder<UDataTable> TableObj(
	TEXT("/Game/TopDown/Blueprints/DT_ItemData.DT_ItemData"));
	
	// If the item data table is found, initialize the data table and the row name for the "AmmoItemRow"
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
	
	
	// Set the "Owning Character"
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
	// Set the parameters for the "Spawn Actor" function
	FActorSpawnParameters Params;
	Params.Owner = GetOwner();
	Params.Instigator = Cast<APawn>(GetOwner());

	// Spawn the projectile
	GetWorld()->SpawnActor<AGunProjectile>(
		ProjectileClass,
		 GetOwner()->GetActorLocation() + 
		 GetOwner()->GetActorForwardVector() * 75.f,
		GetOwner()->GetActorRotation(),
		Params
	);
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Black,"Weapon fired");

	// Send request to affect the ammo count of the shooter
	RequestAffectAmmo(AmmoItemRow,1);
}

void UWeaponSystem::RequestAffectAmmo(const FDataTableRowHandle& AmmoType,const int Amount) const
{
	// Affect the ammo of the shooter 
	OwningCharacter->AffectAmmo(AmmoItemRow,Amount);
}

