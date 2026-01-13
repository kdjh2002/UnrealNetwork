// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PracticeCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

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

public:
	//리플리케이션을 설정을 위한 필수 함수 오버라이드 
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void Onkey1();

	UFUNCTION()
	void Onkey2();

	UFUNCTION()
	void Onkey3();

private:
	UFUNCTION()
	void OnRef_Level();

	UFUNCTION()
	void OnRef_Exp();

	UFUNCTION()
	void OnRef_Health();

	void UpdateLevel();
	void UpdateExp();
	void UpdateHealth();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UWidgetComponent> HealthWidgetComponent = nullptr;

	//리플리케이션 끝났을때 실행될 함수(위젯을 위해)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRef_Level, Category = "Stats")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRef_Health, Category = "Stats")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRef_Exp, Category = "Stats")
	float Exp = 0.0f;

private:
	UPROPERTY()
	TWeakObjectPtr<class UDataLineWidget> HealthWidget = nullptr;
};
