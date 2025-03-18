// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Weapon_Hitscan.generated.h"

UCLASS()
class PROJECTBARTENDER_API AWeapon_Hitscan : public AWeapon_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_Hitscan();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Fire(FVector Reticle, FVector Direction) override;
};
