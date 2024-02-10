// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/OmniAbilitySystemComponent.h"

#include "DebugMacros.h"


void UOmniAbilitySystemComponent::Init()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UOmniAbilitySystemComponent::EffectApplied);
}

void UOmniAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                        const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle GameplayEffectHandle)
{
	PRINT_DEBUG_MESSAGE(1.f, FColor::Red, FString("Effect Applied!!!"));
}
