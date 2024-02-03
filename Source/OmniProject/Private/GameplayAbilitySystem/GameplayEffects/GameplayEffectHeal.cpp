// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/GameplayEffects/GameplayEffectHeal.h"

#include "GameplayAbilitySystem/OmniAttributeSet.h"

UGameplayEffectHeal::UGameplayEffectHeal()
{
	const FGameplayAttribute GameplayAttribute(UOmniAttributeSet::GetHealthAttribute());
	const FGameplayModifierInfo ModifierInfo(GameplayAttribute, EGameplayModOp::Additive, FGameplayEffectModifierMagnitude(HealPoints));
	Modifiers.Add(ModifierInfo);
}
