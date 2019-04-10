// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnManager.h"
#include "Core/Public/Math/UnrealMathUtility.h"
#include "Engine/World.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnInterval, this, &ASpawnManager::SpawnEntity, FMath::RandRange(minSpawnTime, maxSpawnTime), true, 0.0f);
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnManager::SpawnEntity()
{
	//GetWorldTimerManager().SetTimer(FireTimer, this, &AAssaultWeapon::WeaponTrace, FireRate, true, 0.0f);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Entity called!"));

	// This following code assumes that the TArray of TargetPoints has AT LEAST one declared member!
	// If not, the game will crash on simulation/play.
	int index = FMath::RandRange(0, SpawnPoints.Num() - 1); // Note: RandRange is inclusive on both ends
	FActorSpawnParameters SpawnInfo;
	if (GetWorld())
	{
		ADwarfCharacter * NewlySpawned = GetWorld()->SpawnActor<ADwarfCharacter>(TargetSpawn, (const FVector)(SpawnPoints[index]->GetActorLocation()), FRotator::ZeroRotator);
		NewlySpawned->SpawnDefaultController();
	}
}