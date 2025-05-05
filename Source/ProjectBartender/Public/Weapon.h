// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapon.generated.h"

class AProjectile;
class UArrowComponent;
UCLASS(Blueprintable)
class PROJECTBARTENDER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();
	
	//Attempt to fire
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	bool TryFiring(FVector Reticle, FVector Direction, int timesToRicochet);

	//Blueprint event intended to trigger one of the shooting mechanics
	UFUNCTION(BlueprintNativeEvent, Category = "Shooting")
	void OnFire(int timesToRicochet);
	
	//Different ways of shooting
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Fire_Hitscan_Spread(int BulletsPerShot, float MinSpread, float MaxSpread, bool& CriticalHit, AActor*& ActorHit);
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Fire_Hitscan_Single(bool& CriticalHit, AActor*& ActorHit);
	UFUNCTION(BlueprintCallable, Category= "Shooting")
	void Fire_Hitscan_Ricochet(FVector RicochetStart, AActor* TargetActor, TArray<AActor*> ActorsToIgnore, bool& Success);
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Fire_Projectile(TSubclassOf<AProjectile> projectile, FVector direction);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reload();
	UFUNCTION()
	void ResetCooldown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> _Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FireRange = 12000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Damage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FireRate = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool GunCooldown = false;
	

	//Ammo variables for reloading and storing data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int AmmoInClip; //Ammo in the gun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int ClipCapacity; //How much the gun can hold

	UPROPERTY(EditAnywhere)
	TObjectPtr<UArrowComponent> _Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

private:
	FVector Reticle;
	FVector Direction;
	
	FTimerHandle _CooldownResetTimer;
	
};
