
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EGrade.h"
#include "WeaponComponent.generated.h"


class AProjectile;
class UArrowComponent;


UCLASS(ClassGroup=(Weapon), Abstract, Blueprintable)
class PROJECTBARTENDER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UWeaponComponent();
	
	//Attempt to fire
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	bool TryFiring(FVector start, FVector forward, EGrade grade);

	//Blueprint event intended to trigger one of the shooting mechanics
	UFUNCTION(BlueprintNativeEvent, Category = "Shooting")
	void OnFire(int bouncesLeft);
	
	//shooting
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Fire_Hitscan_Single(bool& CriticalHit, AActor*& ActorHit);
	UFUNCTION(BlueprintCallable, Category= "Shooting")
	void Fire_Hitscan_Ricochet(FVector RicochetStart, AActor* TargetActor, TArray<AActor*> ActorsToIgnore, bool& Success);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reload();
	UFUNCTION()
	void ResetCooldown();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FireRange = 2000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Damage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FireRate = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float SFXVolume = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool GunCooldown = false;
	

	//Ammo variables for reloading and storing data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int AmmoInClip; //Ammo in the gun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int ClipCapacity; //How much the gun can hold

	UPROPERTY(BlueprintReadWrite)
	int timesToRicochet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* Shot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* FailedShot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
private:
	FVector Reticle;
	FVector Direction;
	
	FTimerHandle _CooldownResetTimer;
	
	
};
