// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ConnectionCharacter.h"
#include "NetRoleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALNETWORK_API ANetRoleCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ANetRoleCharacter();

protected:
	virtual void Tick(float DeltaTime) override;
};
