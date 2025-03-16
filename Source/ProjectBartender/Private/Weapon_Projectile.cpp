// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Projectile.h"

#include "Projectile.h"
#include "Components/ArrowComponent.h"
#include "Tasks/GameplayTask_SpawnActor.h"


// Sets default values
AWeapon_Projectile::AWeapon_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;

	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Mesh);
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

	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	world->SpawnActor(_ProjectileClass, &_Muzzle->GetComponentTransform(), spawnParams);
}


