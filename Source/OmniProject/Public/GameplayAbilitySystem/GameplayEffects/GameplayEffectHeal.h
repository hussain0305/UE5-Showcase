// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectHeal.generated.h"

/**
 * 
 */
UCLASS()
class OMNIPROJECT_API UGameplayEffectHeal : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UGameplayEffectHeal();

	float HealPoints = 25.f;
};
