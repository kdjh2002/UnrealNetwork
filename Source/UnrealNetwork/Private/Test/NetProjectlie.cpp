// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NetProjectlie.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ANetProjectlie::ANetProjectlie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true; 
	SetReplicateMovement(true);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(20.0f);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(Collision);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	//Movement->UpdatedComponent = Collision;
	Movement->MaxSpeed = 1000.0f;
	Movement->bShouldBounce = true;
}

// Called when the game starts or when spawned
void ANetProjectlie::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ANetProjectlie::OnHit);

	if (GetInstigator())
	{
		//인스티게이터가 설정되어 있으면 충돌 무시하기
		Collision->IgnoreActorWhenMoving(GetInstigator(), true); 
	}
	
}

void ANetProjectlie::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())	// 서버에서만 히트 처리
	{
		if (!bHitted && OtherActor->IsA<ACharacter>() // 한번도 충돌한적 없고, 캐릭터와 캐릭터의 파생클래스만 처리
			&& this != OtherActor && GetOwner() != OtherActor)	
		{
			// 데미지 주기

			UGameplayStatics::ApplyDamage(OtherActor, 10.0f, GetInstigatorController(), this, UDamageType::StaticClass());

			if (GetInstigator())
			{
				UE_LOG(LogTemp, Log, TEXT("%s가 %s를 공격했다."), *GetInstigator()->GetName(), *OtherActor->GetName());
				// 누가 누구를 공격했는지 출력
			}

			Multicast_HitEffect(Hit.ImpactPoint, Hit.ImpactNormal.Rotation());	// 모두에게 이팩트 ㅈ
			SetLifeSpan(2.0f);	//2초뒤에 삭제
			bHitted = true;		//처음 Hit되었음을 기록
		}
	}
}

void ANetProjectlie::Multicast_HitEffect(const FVector& InLocation, const FRotator& InRotation)
{
	if (HitEffectClass)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffectClass, InLocation, InRotation);
	}
}


