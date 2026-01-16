// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PracticeCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"
#include "UI/DataLineWidget.h"
#include "Framework/PracticePlayerController.h"

// Sets default values
APracticeCharacter::APracticeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APracticeCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthWidgetComponent && HealthWidgetComponent->GetWidget())
	{
		HealthWidget = Cast<UDataLineWidget>(HealthWidgetComponent->GetWidget());
		HealthWidget->UpdateName(FText::FromString(TEXT("Health")));

	}
	
}

// Called every frame
void APracticeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (HealthWidgetComponent)
	//{
	//	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	//	if (PC && PC->PlayerCameraManager)
	//	{
	//		//회전->벡터만들기 가능
	//		//벡터->회전만들기 가능

	//		FVector CameraForward = PC->PlayerCameraManager->GetCameraRotation().Vector();	//카메라의 Forward벡터
	//		FVector WidgetForward = CameraForward * -1.0f;
	//		HealthWidgetComponent->SetWorldRotation(WidgetForward.Rotation());
	//	}
	//}
}

// Called to bind functionality to input
void APracticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//컨트롤러에 입력넣음
}

void APracticeCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(APracticeCharacter, Level, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(APracticeCharacter, Exp, COND_OwnerOnly);
	DOREPLIFETIME(APracticeCharacter, Health);	//모두에게 리플리케이션
}

void APracticeCharacter::OnRef_Level()
{
	UpdateLevel();
}

void APracticeCharacter::OnRef_Exp()
{
	UpdateExp();
}
void APracticeCharacter::OnRef_Health()
{
	UpdateHealth();	//클라이언트는 리플리케이션을 받아서 업데이트
}

void APracticeCharacter::UpdateLevel()
{
	OnLevelUpdated.Execute(Level);
}

void APracticeCharacter::UpdateExp()
{
	OnLevelUpdated.Execute(Exp);
}

void APracticeCharacter::UpdateHealth()
{
	if (HealthWidget.IsValid())
	{
		HealthWidget->UpdateFloatValue(Health);
	}
}


void APracticeCharacter::Onkey1()
{
	if (HasAuthority())		//서버쪽에서
	{
		Level++;
		UpdateLevel();
	}
}

void APracticeCharacter::Onkey2()
{
	if (HasAuthority())
	{
		Exp += 1.0f;
		UpdateExp();
	}
}

void APracticeCharacter::Onkey3()
{
	if (HasAuthority())
	{
		Health -= 10.0f;
		UpdateHealth();
	}
}

