// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GASPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GAS/TestAttributeSet.h"
#include "GameplayEffectTypes.h"

AGASPlayerState::AGASPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	ResourceAS = CreateDefaultSubobject<UTestAttributeSet>(TEXT("Resoucre"));

	//SetNetUpdateFrequency(100.0f);
}

void AGASPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetDefaultAbilitySystemData();
	}
}

void AGASPlayerState::SetDefaultAbilitySystemData()
{
	if (HasAuthority() && ASC)
	{
		for (TSubclassOf<UGameplayAbility>& AbilityClass : DefaultAbilities)
		{
			if (AbilityClass)
			{
				ASC->GiveAbility(
					FGameplayAbilitySpec(AbilityClass, 1, -1, this));
			}
		}
	}

	for (TSubclassOf<UGameplayEffect>& EffectClass : DefaultEffects)
	{
		if (EffectClass)
		{
			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1, EffectContext);

			if (SpecHandle.IsValid())
			{
				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}

}
