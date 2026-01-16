// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameStateMainHudWidget.h"
#include "Framework/TestGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UGameStateMainHudWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateTimeDisplay();
}

void UGameStateMainHudWidget::UpdateTimeDisplay()
{
	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(this));
	}

	if (CachedGameState.IsValid())
	{
		int32 Total = FMath::FloorToInt(CachedGameState->GetGameElapsedTime());
		int32 Minutes = Total / 60;
		int32 Seconds = Total % 60;

		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

