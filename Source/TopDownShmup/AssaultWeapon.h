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
	
	virtual void OnStartFire();
	virtual void OnStopFire();
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	UParticleSystem* HitEffects;
	FTimerHandle FireTimer;
	void WeaponTrace();

public:
};
