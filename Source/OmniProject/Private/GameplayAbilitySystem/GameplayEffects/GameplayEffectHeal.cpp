// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/GameplayEffects/GameplayEffectHeal.h"

#include "GameplayAbilitySystem/OmniAttributeSet.h"

UGameplayEffectHeal::UGameplayEffectHeal()
{
	FGameplayAttribute GameplayAttribute(UOmniAttributeSet::GetHealthAttribute());
	FGameplayModifierInfo ModifierInfo(GameplayAttribute, EGameplayModOp::Additive, FGameplayEffectModifierMagnitude(HealPoints));
	Modifiers.Add(ModifierInfo);
}
