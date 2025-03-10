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
	
	UE_LOG(LogTemp, Warning, TEXT("YIPPPEEEEE"));
}

void AWeapon_Base::StopFiring()
{
	
}
