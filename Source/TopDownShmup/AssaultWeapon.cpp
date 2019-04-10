 // Fill out your copyright notice in the Description page of Project Settings.

#include "AssaultWeapon.h"
#include "DwarfCharacter.h"

AAssaultWeapon::AAssaultWeapon()
{
	FireRate = 0.05f;
	WeaponRange = 1000.0f;
	DMG = 2;
}

void AAssaultWeapon::OnStartFire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Ran trace"));
	GetWorldTimerManager().SetTimer(FireTimer, this, &AAssaultWeapon::WeaponTrace, FireRate, true, 0.0f);
	Super::OnStartFire();
}

void AAssaultWeapon::OnStopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimer);
	Super::OnStopFire();

}

void AAssaultWeapon::WeaponTrace()
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
	static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));

	// Start from the muzzle's position
	FVector StartPos = WeaponMesh->GetSocketLocation(MuzzleSocket);

	// Get forward vector of MyPawn
	FVector Forward = MyPawn->GetActorForwardVector();

	// Calculate end position
	FVector EndPos = StartPos + (Forward * WeaponRange);

	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	// This fires the ray and checks against all objects w/ collision
	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos,
		FCollisionObjectQueryParams::AllObjects, TraceParams);

	// Did this hit anything?
	if (Hit.bBlockingHit)
	{
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffects, FVector(Hit.Location.X, Hit.Location.Y, Hit.Location.Z));
		//UE_LOG(LogTemp, Warning, TEXT("TraceHit"));
		ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(Hit.GetActor());
		if (Dwarf)
		{
			Dwarf->TakeDamage(DMG, FDamageEvent(), GetInstigatorController(), this);
		}
	}
}