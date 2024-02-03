// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OmniPlayerState.h"
#include "GameplayAbilitySystem/OmniAbilitySystemComponent.h"
#include "GameplayAbilitySystem/OmniAttributeSet.h"

AOmniPlayerState::AOmniPlayerState()
{
	NetUpdateFrequency = 60.0f;
	
	AbilitySystemComponent = CreateDefaultSubobject<UOmniAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UOmniAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AOmniPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
