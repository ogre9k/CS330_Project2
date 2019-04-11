// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyingBullet.h"
#include "DwarfCharacter.h"
#include "TopDownShmupCharacter.h"

// Sets default values
AFlyingBullet::AFlyingBullet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DMG = 10;
	/*
	TArray<USphereComponent*> sphereComponents;
	GetComponents<USphereComponent>(sphereComponents);
	sphereComponents[0]->OnComponentBeginOverlap.AddDynamic(this, &AFlyingBullet::OnOverlapBegin);
	sphereComponents[0]->OnComponentEndOverlap.AddDynamic(this, &AFlyingBullet::OnOverlapEnd);
	*/

	// Create static mesh
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMesh;
	BulletMesh->OnComponentBeginOverlap.AddDynamic(this, &AFlyingBullet::OnOverlapBegin);
	
}

void AFlyingBullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap!"));
	ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(OtherActor);
	if (Dwarf)
	{
		Dwarf->TakeDamage(DMG, FDamageEvent(), GetInstigatorController(), this);
		Destroy();
	}
}

void AFlyingBullet::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	;
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
	FVector NewLocation = GetActorLocation() + (MovementVector * 1000 * DeltaTime);
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void AFlyingBullet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

