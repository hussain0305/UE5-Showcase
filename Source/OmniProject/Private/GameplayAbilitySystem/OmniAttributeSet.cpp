// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/OmniAttributeSet.h"
#include "Net/UnrealNetwork.h"

UOmniAttributeSet::UOmniAttributeSet()
{
}

void UOmniAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UOmniAttributeSet, Health,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOmniAttributeSet, MaxHealth,	COND_None, REPNOTIFY_Always);
}

void UOmniAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOmniAttributeSet, Health, OldHealth);
}

void UOmniAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOmniAttributeSet, MaxHealth, OldMaxHealth);
}
