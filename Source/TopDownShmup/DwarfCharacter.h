// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "DwarfCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API ADwarfCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	ADwarfCharacter();
	void StartAttack();
	void StopAttack();

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* AttackAnim;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnim;

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, Category = "Combat")
	float HP;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float DMG;
	FTimerHandle DeathTimer;
	FTimerHandle AttackTimer;

	void DamagePlayer();
	void Kill();
};
