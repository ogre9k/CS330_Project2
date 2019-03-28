// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "TopDownShmupPlayerController.generated.h"

UCLASS()
class ATopDownShmupPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATopDownShmupPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface



	/** Navigate player using WASD */
	void MoveForward(float Value);
	void MoveRight(float Value);


	/** Shooting */
	void OnStartFire();
	void OnStopFire();

	/** Have player face mouse location */
	void UpdateMouseLook();

};


