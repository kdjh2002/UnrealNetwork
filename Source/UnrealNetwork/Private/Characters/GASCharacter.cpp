// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GASCharacter.h"
#include "GAS/TestAttributeSet.h"
#include "UI/DataLineWidget.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AGASCharacter::AGASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	//Minimal : 어트리뷰트와 큐민 오너와 다른 클라이언트에게 리플리케이션 (ex : NPC적)
	//Mixed : 미니멀 + (오너에게 모두 리플리케이션) (ex : 자기 플레이어)
	//Full : 모두에게 모두 리플리케이션(디버깅, 관전모드용)

	ResourceAttributeSet = CreateDefaultSubobject<UTestAttributeSet>(TEXT("ResourceGAS"));

	//UI
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComp"));
	Widget->SetupAttachment(GetRootComponent());
	Widget->SetRelativeLocation(FVector::UpVector * 105.0f);

}

// Called when the game starts or when spawned
void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority() && ASC && AbilityClass)
	{
		ASC->InitAbilityActorInfo(this, this);

		FOnGameplayAttributeValueChange& onHealthChange = 
			ASC->GetGameplayAttributeValueChangeDelegate(UTestAttributeSet::GetHealthAttribute());
		onHealthChange.AddUObject(this, &AGASCharacter::OnHealthChanged);

		if (Widget && Widget->GetWidget())
		{
			UDataLineWidget* HealthWidget = Cast<UDataLineWidget>(Widget->GetWidget());
			HealthWidget->UpdateName(FText::AsNumber(ResourceAttributeSet->GetHealth()));
			HealthWidget->UpdateIntValue(FMath::FloorToInt32(ResourceAttributeSet->GetMaxHealth()));
		}
		if (HasAuthority())
		{
		ASC->GiveAbility(
			FGameplayAbilitySpec(AbilityClass, 1, -1, this));

		}

	}
	
}

// Called every frame
void AGASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGASCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	const float NewHealth = Data.NewValue;
	UE_LOG(LogTemp, Log, TEXT("현재 체력 : %.1f"), NewHealth);

	if (Widget && Widget->GetWidget())
	{
		UDataLineWidget* HealthWidget = Cast<UDataLineWidget>(Widget->GetWidget());
		HealthWidget->UpdateName(FText::AsNumber(NewHealth));
		HealthWidget->UpdateIntValue(FMath::FloorToInt32(ResourceAttributeSet->GetMaxHealth()));
	}
}

void AGASCharacter::TestActivateAbility()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("TestActivateAbility 시작"));
	if (ASC)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("TestActivateAbility : ASC 있음"));
		bool Result = ASC->TryActivateAbilityByClass(AbilityClass);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
			FString::Printf(TEXT("TestActivateAbility : %s"),
				Result ? TEXT("성공") : TEXT("실패")));
	}
}