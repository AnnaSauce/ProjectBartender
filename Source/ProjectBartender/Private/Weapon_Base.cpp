// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Base.h"

// Sets default values
AWeapon_Base::AWeapon_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);
}

void AWeapon_Base::Fire_Implementation(FVector Reticle, FVector Direction)
{
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	UWorld* const world = GetWorld();
}

void AWeapon_Base::StartFiring(FVector Reticle, FVector Direction)
{
	//If the gun has ammo, allow it to fire.
	if(AmmoInClip > 0 && !GunCooldown)
	{
		GunCooldown = true;
		AmmoInClip--;
		Fire(Reticle, Direction); //Animation trigger might need to be called through this function

		//Set a timer for the weapon cooldown. The time is 1/x so that the higher the rate is, the faster it shoots.
		GetWorld()->GetTimerManager().SetTimer(_CooldownResetTimer, this, &AWeapon_Base::ResetCooldown, 1/FireRate, true);
		
	}
}

void AWeapon_Base::Reload_Implementation()
{
	AmmoInClip = ClipCapacity; //Delete this line if stored ammo will be used.
	
	//Below commented code is for if there will be stored ammo as for now there is no ammo inventory
	/*int ammoNeeded = ClipCapacity - AmmoInClip;
	if(TotalAmmo >= ammoNeeded)
	{
		TotalAmmo -= ammoNeeded;
		AmmoInClip = ClipCapacity;
	}*/
}

void AWeapon_Base::ResetCooldown()
{
	GunCooldown = false;
}


