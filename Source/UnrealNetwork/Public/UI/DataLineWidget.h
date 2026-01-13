// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataLineWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class UNREALNETWORK_API UDataLineWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdataName(FText InName);

	UFUNCTION(BlueprintCallable)
	void UpdataIntValue(int32 InValue);

	UFUNCTION(BlueprintCallable)	
	void UpdataFloatValue(float InValue);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Name = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Value = nullptr;
};
