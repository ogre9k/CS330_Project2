// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEnemyController.h"
#include "DwarfCharacter.h"
#include "AIDwarfController.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAIDwarfState : uint8
{
	EStart,
	EChasePlayer,
	EAttackPlayer,
	EDead
};

UCLASS()
class TOPDOWNSHMUP_API AAIDwarfController : public AAIEnemyController
{
	GENERATED_BODY()
	

public:
	void BeginPlay();
	void OnPossess(APawn *inPawn);
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
	void SetCurrentState(EAIDwarfState NewState);
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Range")
	float Range;

private:
	ADwarfCharacter* MyDwarf;
	EAIDwarfState CurrentState;
	void HandleNewState(EAIDwarfState NewState);
};
