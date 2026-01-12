// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NetRoleCharacter.h"

ANetRoleCharacter::ANetRoleCharacter()
{
	PrimaryActorTick.bCanEverTick = true; // 이 줄이 true여야 Tick이 동작합니다.
}

void ANetRoleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FString LocalRoleString = UEnum::GetValueAsString(GetLocalRole());
	const FString RemoteRoleString = UEnum::GetValueAsString(GetRemoteRole());

	const FString OwnerString = GetOwner() ? GetOwner()->GetName() : TEXT("오너 없음");
	const FString ConnectionString = GetNetConnection() ? TEXT("커넥션 있음") : TEXT("커넥션 없음");

	const FString NetworkInfo = FString::Printf(
		TEXT("LocalRole : %s\nRemoteRole : %s\nOwner : %s\nConnection : %s"),
		*LocalRoleString, *RemoteRoleString, *OwnerString, *ConnectionString);
	DrawDebugString(GetWorld(), GetActorLocation(), NetworkInfo, nullptr, FColor::Green, 0.0f, true);
}

