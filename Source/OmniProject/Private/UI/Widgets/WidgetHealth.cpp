// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/WidgetHealth.h"

#include "GameplayAbilitySystem/OmniAttributeSet.h"
#include "UI/OmniHUDController.h"

void UWidgetHealth::InitHUDValue()
{
	Super::InitHUDValue();
	UpdateValue(GetHUDController()->GetAttributeSet()->Health.GetCurrentValue());
}

void UWidgetHealth::UpdateValue(float newValue)
{
	Super::UpdateValue(newValue);

	//TODO: Get text component from the BP and just write it directly here.

	BP_UpdateValue(newValue);
}

void UWidgetHealth::BindListenerDelegate()
{
	GetHUDController()->OnHealthChanged.AddDynamic(this, &UWidgetHealth::UpdateValue);
}
