// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestGameState.h"
#include "Net/UnrealNetwork.h"

ATestGameState::ATestGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		GameElapsedTime += DeltaTime;
		UE_LOG(LogTemp, Log, TEXT("Time Update : %.2f"), GameElapsedTime);
	}
}

void ATestGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestGameState, GameElapsedTime);		//#include "Net/UnrealNetwork.h"
}
