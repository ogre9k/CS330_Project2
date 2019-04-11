// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyingBullet.h"
#include "TopDownShmupCharacter.h"

// Sets default values
AFlyingBullet::AFlyingBullet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlyingBullet::BeginPlay()
{
	Super::BeginPlay();
	ATopDownShmupCharacter* PlayerCharacter = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
		MovementVector = PlayerCharacter->GetActorForwardVector();
}

// Called every frame
void AFlyingBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation() + (MovementVector * 150 * DeltaTime);
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void AFlyingBullet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

