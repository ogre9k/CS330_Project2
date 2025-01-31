// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Components/AudioComponent.h"
#include "Engine/Classes/Sound/SoundCue.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TOPDOWNSHMUP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	virtual void OnStartFire();
	virtual void OnStopFire();
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Transient)
	UAudioComponent* FireAC;

	UAudioComponent* PlayWeaponSound(USoundCue*);

	UPROPERTY(Transient)
	UParticleSystemComponent* FirePSC;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DMG;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* FireLoopSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* FireFinishSound;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* MuzzleFX;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float FireRate;
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float WeaponRange;
	APawn * MyPawn;
};
