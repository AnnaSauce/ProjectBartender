// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Projectile.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);
	_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Mesh);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

bool AWeapon::TryFiring(FVector start, FVector forward, int timesToRicochet)
{
	//If the gun has ammo, allow it to fire.
	if(AmmoInClip > 0 && !GunCooldown)
	{
		GunCooldown = true;
		Reticle = start;
		Direction = forward;
		AmmoInClip--;
		OnFire(); //Animation trigger might need to be called through this function

		//Set a timer for the weapon cooldown. The time is 1/x so that the higher the rate is, the faster it shoots.
		GetWorld()->GetTimerManager().SetTimer(_CooldownResetTimer, this, &AWeapon::ResetCooldown, 1/FireRate, true);
		return true;
	}
	return false;
}

void AWeapon::OnFire_Implementation()
{
	//return false;
}

void AWeapon::Reload_Implementation()
{
	AmmoInClip = ClipCapacity;
}

void AWeapon::ResetCooldown()
{
	GunCooldown = false;
}

void AWeapon::Fire_Hitscan_Spread(int BulletsPerShot, float MinSpread, float MaxSpread, bool& CriticalHit, AActor*& ActorHit)
{
	CriticalHit = false;
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }

	//Set parameters for new line trace
	FHitResult hit(ForceInit);
	FVector start = Reticle;
	FVector end = Reticle+(Direction*FireRange);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	int BulletsHit = 0;
	
	for(int i = 0; i < BulletsPerShot; i++)
	{
		//Randomise this iteration's end position
		FVector newEnd = end;
		newEnd.X+=FMath::RandRange(MinSpread,MaxSpread);
		newEnd.Y+=FMath::RandRange(MinSpread,MaxSpread);
		newEnd.Z+=FMath::RandRange(MinSpread,MaxSpread);
		
		if(UKismetSystemLibrary::LineTraceSingle(world, start, newEnd,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel3), false, ActorsToIgnore,
		EDrawDebugTrace::Persistent, hit, true, FLinearColor::Red,
		FLinearColor::Green, 1))
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
			ActorHit = hit.GetActor();
		}
	}
	
}

void AWeapon::Fire_Hitscan_Single(TArray<AActor*> ActorsToIgnore, AActor* ricochetTarget,
	bool& CriticalHit, AActor*& ActorHit, UPrimitiveComponent*& HitComponent)
{
	//Reset Vaues
	HitComponent = nullptr;
	CriticalHit = false;
	
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }
	FVector start;
	FVector end;
	//Set parameters for new line trace
	FHitResult hit(ForceInit);
	if(ricochetTarget == nullptr)
	{
		start = Reticle;
		end = Reticle+(Direction*FireRange);
	}
	else
	{
		start = ActorHit->GetActorLocation();
		end  = ricochetTarget->GetActorLocation();
	}
	ActorHit = nullptr;

	if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel3), false, ActorsToIgnore,
		EDrawDebugTrace::Persistent, hit, true, FLinearColor::Red,
		FLinearColor::Green, 1))
	{
		//Check if line hit an actor
		if(hit.GetActor())
		{
			HitComponent = hit.GetComponent();
			if(hit.GetComponent()->ComponentHasTag(FName("Critical")))
			{
				CriticalHit = true;
				Damage*=2;
			}
			
			//Apply damage
			UGameplayStatics::ApplyDamage(hit.GetActor(), Damage,
			GetOwner()->GetInstigatorController(), GetOwner(),
			UDamageType::StaticClass());
			ActorHit = hit.GetActor();
		}
	}
}

void AWeapon::Fire_Projectile(TSubclassOf<AProjectile> projectile, FVector direction)
{
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }
	
	//Set spawn parameters
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	//Spawn projectile
	AProjectile* projectileShot = Cast<AProjectile>(world->SpawnActor(projectile, &_Muzzle->GetComponentTransform(), spawnParams));
	projectileShot->Damage = Damage;
}


