// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Weapon_Projectile.generated.h"

class UArrowComponent;

UCLASS()
class PROJECTBARTENDER_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Fire_Implementation(FVector Reticle, FVector Direction) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UArrowComponent> _Arrow;
};
