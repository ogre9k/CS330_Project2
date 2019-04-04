// Fill out your copyright notice in the Description page of Project Settings.

#include "AIDwarfController.h"
#include "TopDownShmupCharacter.h"
void AAIDwarfController::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentState(EAIDwarfState::EStart);
}

void AAIDwarfController::Tick(float DeltaTime)
{
	if (CurrentState == EAIDwarfState::EStart) 
	{
		SetCurrentState(EAIDwarfState::EChasePlayer);
	}

	if (CurrentState == EAIDwarfState::EAttackPlayer)
	{
		ATopDownShmupCharacter* PlayerCharacter = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (PlayerCharacter)
		{
			//if (Range < (PlayerCharacter->GetActorLocation() - MyDwarf->GetActorLocation()).Size())
			//{
				SetCurrentState(EAIDwarfState::EChasePlayer);
			//}
		}
	}
	
}

void AAIDwarfController::OnPossess(APawn *inPawn)
{
	Super::Possess(inPawn);
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
	if (NewState == EAIDwarfState::EChasePlayer)
	{
		ATopDownShmupCharacter* PlayerCharacter = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (PlayerCharacter)
		{
			MoveToActor(PlayerCharacter);
		}
	}
}