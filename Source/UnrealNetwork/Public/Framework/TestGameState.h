// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TestGameState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALNETWORK_API ATestGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATestGameState();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	inline float GetGameElapsedTime() const { return GameElapsedTime; }
	inline float GetGameRemainingTime() const { return GameElapsedTime; }

	inline bool IsGameOver() const { return bGameOver; }

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float GameElapsedTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = "Game Data")
	float GameDuration = 10.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float GameRemainingTime = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	bool bGameOver = false;
};
