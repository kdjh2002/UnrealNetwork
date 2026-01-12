// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PracticeCharacter.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APracticeCharacter::APracticeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APracticeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APracticeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		//Level++;
		//Exp += 0.1f;
		//Health += 1.0f;
	}
	const FString Str = FString::Printf(TEXT("Lv(%d), Exp(%.1f), Health(%.1f"), Level, Exp, Health);
	DrawDebugString(GetWorld(), GetActorLocation(), Str, nullptr, FColor::Cyan, 0, true);
}

// Called to bind functionality to input
void APracticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APracticeCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APracticeCharacter, Level, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(APracticeCharacter, Exp, COND_SimulatedOnly);
	DOREPLIFETIME(APracticeCharacter, Health);	//모두에게 리플리케이션
}

void APracticeCharacter::Server_UpdateStats(int32 NewLevel, float NewHealth, float NewExp)
{
	Level = NewLevel;
	Health = NewHealth;
	Exp = NewExp;
}

