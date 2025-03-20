// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

UCLASS()
class PROJECTBARTENDER_API AWeapon_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_Base();
	
	UFUNCTION(BlueprintCallable)
	void StartFiring(FVector Reticle, FVector Direction);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reload();
	

	UFUNCTION()
	void ResetCooldown();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire(FVector Reticle, FVector Direction);
	virtual void Fire_Implementation(FVector Reticle, FVector Direction);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FireRange = 2000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Damage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FireRate = 1;

	//Ammo variables for reloading and storing data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int AmmoInClip; //Ammo in the gun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int ClipCapacity; //How much the gun can hold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int TotalAmmo; //Ammo in player inventory

	bool GunCooldown = false;
	FTimerHandle _CooldownResetTimer;

};
