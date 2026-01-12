// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PracticeCharacter.generated.h"

UCLASS()
class UNREALNETWORK_API APracticeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APracticeCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//리플리케이션을 설정을 위한 필수 함수 오버라이드 
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void Server_UpdateStats(int32 NewLevel, float NewHealth, float NewExp);
public:
	UFUNCTION(BlueprintCallable)
	inline void TestSetLevel(int32 InLevel);

	UFUNCTION(BlueprintCallable)
	inline void TestSetHealth(float InHealth);

	UFUNCTION(BlueprintCallable)
	inline void TestSetExp(float InExp);

protected:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* Health


protected:
	UPROPERTY(Replicated)
	int32 Level = 1;

	UPROPERTY(Replicated)
	float Health = 100.0f;

	UPROPERTY(Replicated)
	float Exp = 0.0f;

};
