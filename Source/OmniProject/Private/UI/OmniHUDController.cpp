// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OmniHUDController.h"

#include "GameplayAbilitySystem/OmniAbilitySystemComponent.h"
#include "GameplayAbilitySystem/OmniAttributeSet.h"
#include "HeaderFiles/DebugMacros.h"
#include "HeaderFiles/OmniPlayerDetails.h"

void UOmniHUDController::InitController(FOmniWidgetControllerParams& ControllerParams)
{
	PlayerController		= ControllerParams.PlayerController;
	PlayerState				= ControllerParams.PlayerState;
	AbilitySystemComponent	= ControllerParams.AbilitySystemComponent;
	AttributeSet			= ControllerParams.AttributeSet;

	SetupCallbacksAndDelegates();
	BroadcastInitialValues();
}

void UOmniHUDController::BroadcastInitialValues() const
{
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
}

void UOmniHUDController::SetupCallbacksAndDelegates()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &UOmniHUDController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOmniHUDController::MaxHealthChanged);
}

void UOmniHUDController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOmniHUDController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
