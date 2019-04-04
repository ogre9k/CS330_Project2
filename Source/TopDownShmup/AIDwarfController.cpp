// Fill out your copyright notice in the Description page of Project Settings.

#include "AIDwarfController.h"
#include "TopDownShmupCharacter.h"
#include "Runtime/Core/Public/Math/Vector.h"

AAIDwarfController::AAIDwarfController()
{
	Range = 150.f;
	PrimaryActorTick.bCanEverTick = true;
}
void AAIDwarfController::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentState(EAIDwarfState::EStart);
}

void AAIDwarfController::Tick(float DeltaTime)
{
	if (MyDwarf)
	{
		if (CurrentState == EAIDwarfState::EStart)
		{
			SetCurrentState(EAIDwarfState::EChasePlayer);
		}

		else if (CurrentState == EAIDwarfState::EAttackPlayer)
		{
			ATopDownShmupCharacter* PlayerCharacter = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
			if (PlayerCharacter)
			{
				if (FVector::Dist(PlayerCharacter->GetActorLocation(), MyDwarf->GetActorLocation()) > Range)
				{
					SetCurrentState(EAIDwarfState::EChasePlayer);
				}
			}
		}
	}
	
}

void AAIDwarfController::SetPawn(APawn *inPawn)
{
	Super::SetPawn(inPawn);
	MyDwarf = Cast<ADwarfCharacter>(inPawn);
}

void AAIDwarfController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	SetCurrentState(EAIDwarfState::EAttackPlayer);

}

void AAIDwarfController::SetCurrentState(EAIDwarfState NewState)
{
	CurrentState = NewState;
	HandleNewState(NewState);
}

void AAIDwarfController::HandleNewState(EAIDwarfState NewState)
{
	if (MyDwarf)
	{
		MyDwarf->StopAttack();
		if (NewState == EAIDwarfState::EChasePlayer)
		{
			ATopDownShmupCharacter* PlayerCharacter = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
			if (PlayerCharacter)
			{
				MoveToActor(PlayerCharacter);
			}
		}
		else if (NewState == EAIDwarfState::EAttackPlayer)
		{
			MyDwarf->StartAttack();
		}
	}
}