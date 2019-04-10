// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfCharacter.h"
#include "AIDwarfController.h"
#include "TopDownShmupCharacter.h"

ADwarfCharacter::ADwarfCharacter()
{
	AIControllerClass = AAIDwarfController::StaticClass();
	HP = 20;
	DMG = 10;
}

void ADwarfCharacter::StartAttack()
{
	float AttackDelay = PlayAnimMontage(AttackAnim);
	ATopDownShmupCharacter* PlayerCharacter = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
	{
		GetWorldTimerManager().SetTimer(AttackTimer, this, &ADwarfCharacter::DamagePlayer, AttackDelay, true, AttackDelay/2);
	}
}

void ADwarfCharacter::DamagePlayer()
{
	ATopDownShmupCharacter* PlayerCharacter = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
	{
		if (PlayerCharacter->IsDead())
		{
			StopAnimMontage(AttackAnim);
		}
		else
		{
			PlayerCharacter->TakeDamage(DMG, FDamageEvent(), GetInstigatorController(), this);
			if (PlayerCharacter->IsDead())
			{
				StopAnimMontage(AttackAnim);
			}
		}
	}
}
void ADwarfCharacter::StopAttack()
{
	StopAnimMontage(AttackAnim);
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

float ADwarfCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		HP -= ActualDamage;
		if (HP <= 0.0f)
		{
			//dead
			bCanBeDamaged = false;
			Cast<AAIDwarfController>(GetController())->UnPossess();
			StopAttack();
			float DeathCountdown = PlayAnimMontage(DeathAnim);
			GetWorldTimerManager().SetTimer(DeathTimer, this, &ADwarfCharacter::Kill, DeathCountdown, false, 0.75f);
			UE_LOG(LogTemp, Warning, TEXT("Dorf Dead"));
		}
	}

	return ActualDamage;
}

void ADwarfCharacter::Kill()
{
	Destroy();
}