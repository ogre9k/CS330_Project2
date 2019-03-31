// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "AssaultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API AAssaultWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	AAssaultWeapon();
	
	void OnStartFire();
	void OnStopFire();
	
protected:

	UPROPERTY(EditAnywhere, Category="Weapon Stats")
	float FireRate;
	UPROPERTY(EditAnywhere, Category="Weapon Stats")
	float WeaponRange;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	UParticleSystem* HitEffects;

	void WeaponTrace();

public:
};
