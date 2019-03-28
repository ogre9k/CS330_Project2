// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownShmupPlayerController.h"
#include "TopDownShmup.h"
#include "AI/NavigationSystemBase.h"
#include "TopDownShmupCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ATopDownShmupPlayerController::ATopDownShmupPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDownShmupPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateMouseLook();
}

void ATopDownShmupPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Fire", IE_Pressed, this, &ATopDownShmupPlayerController::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ATopDownShmupPlayerController::OnStopFire);
	InputComponent->BindAxis("MoveForward", this, &ATopDownShmupPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATopDownShmupPlayerController::MoveRight);
}

void ATopDownShmupPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		APawn* const Pawn = GetPawn();
		if (Pawn)
		{
			Pawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
		}
	}
}

void ATopDownShmupPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		APawn* const Pawn = GetPawn();
		if (Pawn)
		{
			Pawn->AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
		}
	}
}

void ATopDownShmupPlayerController::UpdateMouseLook()
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, face it
			FVector FaceDirection = Hit.ImpactPoint - Pawn->GetActorLocation();
			FaceDirection.Z = 0.0f;
			FaceDirection.Normalize();
			Pawn->SetActorRotation(FaceDirection.Rotation());
		}
	}
}

void ATopDownShmupPlayerController::OnStartFire()
{
	ATopDownShmupCharacter* const PlayerCharacter = Cast<ATopDownShmupCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->OnStartFire();
	}
}

void ATopDownShmupPlayerController::OnStopFire()
{
	ATopDownShmupCharacter* const PlayerCharacter = Cast<ATopDownShmupCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->OnStopFire();
	}
}