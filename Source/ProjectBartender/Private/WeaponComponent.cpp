// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"


#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UWeaponComponent::TryFiring(FVector start, FVector forward, EGrade grade)
{
	timesToRicochet = 0;
	if(GunCooldown)return false;
	//If the gun has ammo, allow it to fire.
	if(AmmoInClip > 0)
	{
		GunCooldown = true;
		Reticle = start;
		Direction = forward;
		AmmoInClip--;
		switch (grade)
		{
			case(EGrade::S):
				timesToRicochet = 2;
				break;
			case(EGrade::A):
				timesToRicochet = 1;
				break;
			default:
				timesToRicochet = 0;
				break;
		}
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Shot, GetOwner()->GetActorLocation());
		OnFire(timesToRicochet); //Animation trigger might need to be called through this function
		
		//Set a timer for the weapon cooldown. The time is 1/x so that the higher the rate is, the faster it shoots.
		GetWorld()->GetTimerManager().SetTimer(_CooldownResetTimer, this, &UWeaponComponent::ResetCooldown, 1/FireRate, true);
		return true;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FailedShot, GetOwner()->GetActorLocation());
	return false;
}

void UWeaponComponent::OnFire_Implementation(int bouncesLeft)
{
	
}


void UWeaponComponent::ResetCooldown()
{
	GunCooldown = false;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::Fire_Hitscan_Single(bool& CriticalHit, AActor*& ActorHit)
{
	//Reset Vaues
	CriticalHit = false;
	ActorHit = nullptr;

	//Set parameters for new line trace
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }
	FVector start;
	FVector end;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	FHitResult hit(ForceInit);
	start = Reticle;
	end = Reticle+(Direction*FireRange);

	
	if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel3), false, ActorsToIgnore,
		DrawDebugType, hit, true, FLinearColor::Red,
		FLinearColor::Green, 1))
	{
		//Check if line hit an actor
		if(hit.GetActor()->ActorHasTag("Enemy"))
		{
			
			if(hit.GetComponent()->ComponentHasTag(FName("Critical")))
			{
				CriticalHit = true;
				Damage*=2;
			}
			//Apply damage
			UGameplayStatics::ApplyDamage(hit.GetActor(), Damage,
			GetOwner()->GetInstigatorController(), GetOwner(),
			UDamageType::StaticClass());

			//Return the actor that was hit
			ActorHit = hit.GetActor();
		}
	}
}

void UWeaponComponent::Fire_Hitscan_Ricochet(FVector RicochetStart, AActor* TargetActor, TArray<AActor*> ActorsToIgnore, bool& Success)
{
	//Reset success state
	Success = false;

	//Set parameters for new line trace
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }
	FHitResult hit(ForceInit);
	ActorsToIgnore.Add(GetOwner());
	if(UKismetSystemLibrary::LineTraceSingle(world, RicochetStart, TargetActor->GetActorLocation(),
			UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel3), false, ActorsToIgnore,
			DrawDebugType, hit, true, FLinearColor::Red,
			FLinearColor::Green, 2))
	{
		if(hit.GetActor() == TargetActor)
		{
			//Only damage and continue to ricochet if the line wasn't interrupted on the way
			UGameplayStatics::ApplyDamage(hit.GetActor(), Damage,
			GetOwner()->GetInstigatorController(), GetOwner(),
			UDamageType::StaticClass());
			Success = true;
		}
	}
}

void UWeaponComponent::Reload_Implementation()
{
	AmmoInClip = ClipCapacity;
}
