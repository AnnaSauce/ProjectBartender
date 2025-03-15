// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Base.h"


// Sets default values
AWeapon_Base::AWeapon_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _Mesh;
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon_Base::Fire_Implementation(FVector Reticle, FVector Direction)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire_Implementation"));
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
	
	
	UE_LOG(LogTemp, Warning, TEXT("Reload"));
}

void AWeapon_Base::StopFiring()
{
	
}
