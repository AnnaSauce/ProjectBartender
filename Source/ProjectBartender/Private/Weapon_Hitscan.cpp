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
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }

	//Set parameters for new line trace
	FHitResult hit(ForceInit);
	FVector start = Reticle;
	FVector end = Reticle+(Direction*FireRange);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	
	if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, ActorsToIgnore,
		EDrawDebugTrace::Persistent, hit, true, FLinearColor::Red,
		FLinearColor::Green, 1))
	{

		//Check if line hit an actor
		if(hit.GetActor())
		{
			//Apply damage
			UGameplayStatics::ApplyDamage(hit.GetActor(), Damage,
			GetOwner()->GetInstigatorController(), GetOwner(),
			UDamageType::StaticClass());
		}
	}
}

