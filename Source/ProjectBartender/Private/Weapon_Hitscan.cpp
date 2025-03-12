// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Hitscan.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AWeapon_Hitscan::AWeapon_Hitscan()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AWeapon_Hitscan::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon_Hitscan::Fire_Implementation(FVector Reticle, FVector Direction)
{
	Super::Fire_Implementation(Reticle, Direction);
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }

	FHitResult hit(ForceInit);
	FVector start = Reticle;
	FVector end = start + (Direction*1000);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, ActorsToIgnore,
		EDrawDebugTrace::None, hit, true, FLinearColor::Red,
		FLinearColor::Green, 1))
	{
		
		if(hit.GetActor())
		{
			UGameplayStatics::ApplyDamage(hit.GetActor(), Damage,
			GetOwner()->GetInstigatorController(), GetOwner(),
			UDamageType::StaticClass());
		}
	}
}



