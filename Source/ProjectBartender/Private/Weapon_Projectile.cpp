// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Projectile.h"

#include "Components/ArrowComponent.h"


// Sets default values
AWeapon_Projectile::AWeapon_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Arrow->SetupAttachment(_Mesh);
}

// Called when the game starts or when spawned
void AWeapon_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon_Projectile::Fire_Implementation(FVector Reticle, FVector Direction)
{
	Super::Fire_Implementation(Reticle, Direction);
	UE_LOG(LogTemp, Warning, TEXT("PROJECTILE"));
}


